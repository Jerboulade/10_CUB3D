/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_unsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:51:57 by jcarere           #+#    #+#             */
/*   Updated: 2022/01/15 17:29:21 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_unsigned(t_arg *arg, char *base_tab, int base, uintmax_t n)
{
	int	n_len;
	int	arg_len;

	n_len = ft_count_digit_base(n, base);
	if (arg->precision > n_len)
		arg_len = arg->precision;
	else
		arg_len = n_len;
	arg_len -= (!n && !arg->precision);
	if ((arg->width > arg_len && !arg->just_left && !arg->zero_flag) || \
		(arg->precision != -1 && !arg->just_left && arg->zero_flag))
		ft_putpad(arg->width - arg_len - arg->hash, 0, arg);
	if (arg->hash && arg->spec != 'u')
	{
		arg->return_val += write(arg->fd, "0", 1);
		arg->return_val += write(arg->fd, &arg->spec, 1);
	}
	if (arg->precision > n_len)
		ft_putpad(arg->precision - n_len, 1, arg);
	if (arg->width && arg->precision < 0 && !arg->just_left && arg->zero_flag)
		ft_putpad(arg->width - n_len - arg->hash, 1, arg);
	arg->return_val += display_int(n, arg, base_tab, base);
	if (arg->width > arg_len && arg->just_left)
		ft_putpad(arg->width - arg_len - arg->hash, 0, arg);
}

void	get_unsigned_type(va_list ap, char **format, t_arg *arg)
{
	uintmax_t	n;

	n = va_arg(ap, uintmax_t);
	if (**format == 'p')
		NULL;
	else if (arg->h_length == 2)
		n = (unsigned char)n;
	else if (arg->h_length == 1)
		n = (unsigned short)n;
	else if (arg->l_length == 1)
		n = (unsigned long)n;
	else if (arg->l_length == 2)
		n = (unsigned long long)n;
	else
		n = (unsigned int)n;
	arg->hash *= 2 * (n != 0);
	if (**format == 'p')
		arg->hash = 2;
	if (**format == 'x' || **format == 'p')
		handle_unsigned(arg, "0123456789abcdef", 16, n);
	else if (**format == 'X')
		handle_unsigned(arg, "0123456789ABCDEF", 16, n);
	else
		handle_unsigned(arg, "0123456789", 10, n);
	(*format)++;
}
