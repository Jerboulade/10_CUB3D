/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:52:45 by jcarere           #+#    #+#             */
/*   Updated: 2022/01/15 17:34:12 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	unit_rounding_case(t_fl *f, int k)
{
	int	i;
	int	ulp;
	int	zero;

	i = k;
	ulp = 0;
	zero = 0;
	while (f->f_str[++i] && !ulp)
		ulp = f->f_str[i] != '0';
	f->f_str[k--] = 0;
	zero = (f->f_str[k] == '0');
	if (!ulp)
		f->f_str[k] += (1 - ((f->f_str[k] == '9') * 10)) * (f->f_str[k] % 2);
	else
		f->f_str[k] += (1 - ((f->f_str[k] == '9') * 10));
	while (f->f_str[k] == '0' && !zero)
	{
		if ((k - 1) < 0)
		{
			f->nine = 1;
			break ;
		}
		f->f_str[k - 1] += 1 - ((f->f_str[k - 1] == '9') * 10);
		k--;
	}
}

void	scientific_notation_setup(t_arg *arg, t_fl *flo)
{
	int	i;
	int	j;

	if (arg->spec != 'e')
		return ;
	i = 0;
	j = 0;
	arg->width -= 4 - flo->nb_idigit + 1;
	while (flo->f_str[i] == '0')
		i++;
	if (i && (flo->fl || flo->lfl))
		flo->base_ten = i;
	while (i && flo->f_str[i])
		flo->f_str[j++] = flo->f_str[i++];
	while (i && flo->f_str[j])
		flo->f_str[j++] = '0';
	rounding_float(flo, flo->nb_fdigit + 1);
	if (flo->exp >= 0)
		flo->base_ten = flo->nb_idigit - 1 + flo->nine;
	flo->nb_idigit = 1 - flo->nine;
}

void	scientific_form_exponent(t_arg *arg, t_fl *flo)
{
	if (arg->spec != 'e')
		return ;
	arg->return_val += write(arg->fd, "e", 1);
	if (flo->exp >= 0 || !flo->base_ten)
		arg->return_val += write(arg->fd, "+", 1);
	else
		arg->return_val += write(arg->fd, "-", 1);
	arg->return_val += write(arg->fd, "0", flo->base_ten < 10);
	arg->return_val += display_int(flo->base_ten, arg, "0123456789", 10);
}

void	handle_naninf(t_arg *arg, t_fl *f, char *naninf)
{
	int	is_signed;
	int	len;

	is_signed = (f->sign || arg->plus_flag) * (naninf[0] == 'i');
	len = is_signed + 3;
	if (arg->precision <= len && arg->space_flag && !is_signed)
	{
		arg->return_val += write(arg->fd, " ", 1);
		arg->width--;
	}
	if (arg->width > len && !arg->just_left)
		ft_putpad(arg->width - len, 0, arg);
	arg->return_val += write(arg->fd, "-", (f->sign != 0) * (naninf[0] == 'i'));
	arg->return_val += write(arg->fd, "+", arg->plus_flag && !f->sign);
	arg->return_val += write(arg->fd, naninf, 3);
	if (arg->width > len && arg->just_left)
		ft_putpad(arg->width - len, 0, arg);
}

void	handle_float(t_arg *a, t_fl *flo)
{
	int	len;
	int	is_signed;

	scientific_notation_setup(a, flo);
	is_signed = (flo->sign || a->plus_flag);
	len = flo->nb_totdigit - (a->spec == 'e') - (!a->precision && !a->hash);
	if (a->precision <= len && a->space_flag && !is_signed)
	{
		a->return_val += write(a->fd, " ", 1);
		a->width--;
	}
	if (a->width > len && !a->just_left && !a->zero_flag)
		ft_putpad(a->width - len - is_signed - flo->nine, 0, a);
	a->return_val += write(a->fd, "-", flo->sign != 0);
	a->return_val += write(a->fd, "+", a->plus_flag && !flo->sign);
	if (a->width > len && !a->just_left && a->zero_flag)
		ft_putpad(a->width - len - is_signed - flo->nine, 1, a);
	a->return_val += write(a->fd, "1", flo->nine != 0);
	a->return_val += write(a->fd, flo->f_str, flo->nb_idigit);
	a->return_val += write(a->fd, ".", a->precision != 0 || a->hash != 0);
	a->return_val += write(a->fd, flo->f_str + flo->nb_idigit, flo->nb_fdigit);
	scientific_form_exponent(a, flo);
	if (a->width > len && a->just_left)
		ft_putpad(a->width - len - is_signed - flo->nine, 0, a);
}
