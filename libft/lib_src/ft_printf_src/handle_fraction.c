/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fraction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:52:25 by jcarere           #+#    #+#             */
/*   Updated: 2022/01/10 17:27:42 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_flo(va_list ap, t_arg *arg, t_fl *flo)
{
	flo->big_int = NULL;
	flo->f_str = NULL;
	flo->sc_notation = (arg->spec == 'e');
	flo->nine = 0;
	flo->nb_idigit = 1;
	flo->nb_fdigit = 0;
	flo->nb_totdigit = 0;
	flo->nb_buff = 0;
	flo->base_ten = 0;
	flo->exp = 0;
	flo->sign = 0;
	flo->lfl = 0;
	flo->fl = 0;
	if (arg->long_double_length)
		flo->lfl = va_arg(ap, long double);
	else
		flo->fl = va_arg(ap, double);
	flo->bin_size = (arg->long_double_length * 16) + 64;
	flo->exp_field = (arg->long_double_length * 4) + 12;
	flo->bias = (arg->long_double_length * 15360) + 1023;
	ft_memset(flo->bits, '0', flo->bin_size);
	flo->bits[flo->bin_size] = 0;
}

void	count_idigit(t_fl *flo, t_arg *arg)
{
	long double	tmp;

	if (arg->long_double_length)
		tmp = flo->lfl;
	else
		tmp = flo->fl;
	if (tmp < 0)
		tmp *= -1;
	while (tmp >= 10)
	{
		flo->nb_idigit++;
		(tmp /= 10);
	}
}

int	check_nan_inf(t_fl *flo, t_arg *arg)
{
	int	i;
	int	check_exponent;
	int	check_fraction;

	i = 0;
	check_exponent = 0;
	check_fraction = 0;
	while (++i < flo->exp_field)
		check_exponent += (flo->bits[i] == '1');
	i += arg->long_double_length;
	while (flo->bits[i])
		check_fraction += (flo->bits[i++] == '1');
	if (check_exponent == (flo->exp_field - 1))
	{
		arg->spec = 0;
		if (!check_fraction)
			handle_naninf(arg, flo, "inf");
		else
			handle_naninf(arg, flo, "nan");
		return (1);
	}
	return (0);
}

void	get_bits(int size, t_fl *flo, t_arg *arg)
{
	unsigned char	*ptr;
	int				bit;
	int				i;
	double			fl;
	long double		lfl;

	i = 0;
	fl = flo->fl;
	lfl = flo->lfl;
	if (arg->long_double_length)
		ptr = (unsigned char *)&lfl;
	else
		ptr = (unsigned char *)&fl;
	while (--size >= 0)
	{
		bit = 128;
		while (bit)
		{
			flo->bits[i++] = '0' + ((ptr[size] / bit) > 0);
			ptr[size] -= bit * ((ptr[size] / bit) > 0);
			bit >>= 1;
		}
	}
}

void	handle_fraction(va_list ap, t_arg *arg, char **format)
{
	t_fl	flo;

	(*format)++;
	init_flo(ap, arg, &flo);
	get_bits(flo.bin_size / 8, &flo, arg);
	flo.sign = (flo.bits[0] == '1');
	if (check_nan_inf(&flo, arg))
		return ;
	count_idigit(&flo, arg);
	compute_float(&flo, arg);
	handle_float(arg, &flo);
	if (flo.f_str)
		free(flo.f_str);
	if (flo.big_int)
		free(flo.big_int);
}
