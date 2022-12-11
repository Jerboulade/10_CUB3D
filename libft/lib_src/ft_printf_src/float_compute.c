/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_compute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:52:32 by jcarere           #+#    #+#             */
/*   Updated: 2022/01/10 17:27:14 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	rounding_float(t_fl *flo, int k)
{
	if (!flo->nb_fdigit && flo->f_str[k] == '5')
		unit_rounding_case(flo, k);
	else if (flo->f_str[k] >= '5')
	{
		flo->f_str[k--] = 0;
		flo->f_str[k] += 1 - ((flo->f_str[k] == '9') * 10);
		while (flo->f_str[k] == '0')
		{
			if ((k - 1) < 0)
			{
				flo->nine = 1;
				break ;
			}
			flo->f_str[k - 1] += 1 - ((flo->f_str[k - 1] == '9') * 10);
			k--;
		}
	}
}

void	get_float_string(t_fl *flo, int i, int k, int tot)
{
	int		j;
	char	*str;

	flo->f_str = (char *)malloc(sizeof(char) * (tot + 1));
	if (!flo->f_str)
		return ;
	flo->f_str[tot] = 0;
	while ((++i < flo->nb_buff) && (k < tot))
	{
		str = ft_unitoa_base(flo->big_int[i], "0123456789", 10);
		j = 0;
		if ((flo->exp >= 0 && i) || (flo->exp < 0))
		{
			j = 19 + (!i) - ft_count_digit_base(flo->big_int[i], 10);
			while (--j && (k < tot))
				flo->f_str[k++] = '0';
		}
		while ((k < tot) && (j < (int)ft_strlen(str)))
			flo->f_str[k++] = str[j++];
		free(str);
	}
	while (k < tot)
		flo->f_str[k++] = '0';
	if (!flo->sc_notation)
		rounding_float(flo, flo->nb_totdigit - 1);
}

void	get_exponent(t_fl *flo)
{
	int	i;

	i = 0;
	flo->exp = 0;
	while (++i < flo->exp_field)
	{
		flo->exp += (flo->bits[i] == '1');
		flo->exp <<= 1;
	}
	flo->exp >>= 1;
	flo->exp -= flo->bias;
}

void	fill_zero_fraction(t_fl *flo)
{
	int	len;

	len = flo->nb_fdigit + 1;
	flo->f_str = (char *)malloc(sizeof(char) * (len + 1));
	if (!flo->f_str)
		return ;
	flo->f_str[len] = 0;
	while (--len >= 0)
		flo->f_str[len] = '0';
}

void	compute_float(t_fl *flo, t_arg *arg)
{
	flo->nb_fdigit = 6 + ((arg->precision >= 0) * (arg->precision - 6));
	flo->nb_totdigit = flo->nb_idigit + flo->nb_fdigit + 1 + (arg->spec == 'e');
	flo->nb_buff = (flo->nb_totdigit / 18) + 1 + (arg->spec == 'e');
	if (flo->nb_buff < 6)
		flo->nb_buff = 6 + (arg->spec == 'e');
	flo->big_int = (uintmax_t *)ft_calloc(flo->nb_buff, sizeof(uintmax_t));
	if (!flo->big_int)
		return ;
	flo->big_int[0] = 1000000000000000000;
	if (!flo->fl && !flo->lfl)
		fill_zero_fraction(flo);
	else
	{
		get_exponent(flo);
		sum_mantissa(flo, flo->bits + flo->exp_field + arg->long_double_length);
		if (flo->exp >= 0)
		{
			shift_tab_right(flo);
			mult_big_int(flo, flo->exp, 0, 0);
			shift_tab_left(flo);
		}
		else
			div_big_int(flo->big_int, flo->nb_buff, -flo->exp);
		get_float_string(flo, -1, 0, (flo->nb_buff * 18) + 1);
	}
}
