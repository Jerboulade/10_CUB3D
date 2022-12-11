/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:51:49 by jcarere           #+#    #+#             */
/*   Updated: 2022/01/15 17:29:59 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	display_int(uintmax_t n, t_arg *arg, char *base_tab, char base)
{
	int		i;
	char	integer[20];
	int		precision;

	if (arg->spec == 'e')
		precision = 1;
	else
		precision = arg->precision;
	i = 19;
	if (!n && !precision)
		return (0);
	if (!n)
		integer[i--] = '0';
	while (n)
	{
		integer[i--] = base_tab[n % base];
		n /= base;
	}
	return (write(arg->fd, integer + i + 1, 19 - i));
}

void	handle_int(t_arg *arg, intmax_t n)
{
	int	arg_len;
	int	n_len;

	n_len = ft_count_digit_base(n, 10);
	if (arg->precision > n_len)
		arg_len = arg->precision;
	else
		arg_len = n_len;
	if (arg->precision <= arg_len && arg->space_flag && !(arg->plus_flag % 2))
	{
		arg->return_val += write(arg->fd, " ", 1);
		arg->width--;
	}
	arg_len -= (!n && !arg->precision);
	if ((arg->width > arg_len && !arg->just_left && !arg->zero_flag) || \
		(arg->precision != -1 && !arg->just_left && arg->zero_flag))
		ft_putpad(arg->width - arg_len - (arg->plus_flag % 2), 0, arg);
	arg->return_val += write(arg->fd, &arg->plus_flag, (arg->plus_flag % 2));
	if (arg->precision > n_len)
		ft_putpad(arg->precision - n_len, 1, arg);
	if (arg->width && arg->precision < 0 && !arg->just_left && arg->zero_flag)
		ft_putpad(arg->width - n_len - (arg->plus_flag % 2), 1, arg);
	arg->return_val += display_int(n, arg, "0123456789", 10);
	if (arg->width > arg_len && arg->just_left)
		ft_putpad(arg->width - arg_len - (arg->plus_flag % 2), 0, arg);
}

void	get_signed_type(va_list ap, char **format, t_arg *arg)
{
	intmax_t	n;

	n = va_arg(ap, intmax_t);
	if (arg->h_length == 2)
		n = (char)n;
	else if (arg->h_length == 1)
		n = (short int)n;
	else if (arg->l_length == 1)
		n = (long int)n;
	else if (arg->l_length == 2)
		n = (long long int)n;
	else
		n = (int)n;
	if (arg->plus_flag)
		arg->plus_flag = '+';
	if (n < 0)
	{
		arg->plus_flag = '-';
		n = -n;
	}
	handle_int(arg, n);
	(*format)++;
}
