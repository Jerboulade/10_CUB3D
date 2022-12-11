/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_npc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:52:10 by jcarere           #+#    #+#             */
/*   Updated: 2022/01/15 16:55:07 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_pc(t_arg *arg, char **format)
{
	if (!arg->just_left)
		ft_putpad(arg->width - 1, arg->zero_flag, arg);
	arg->return_val += write(arg->fd, "%", 1);
	if (arg->just_left)
		ft_putpad(arg->width - 1, 0, arg);
	(*format)++;
}

void	handle_nlflag(va_list ap, t_arg *arg)
{
	long		*l_len;
	long long	*ll_len;
	int			*len;

	if (arg->l_length == 1)
	{
		l_len = va_arg(ap, long *);
		*l_len = (long)arg->return_val;
	}
	else if (arg->l_length == 2)
	{
		ll_len = va_arg(ap, long long *);
		*ll_len = (long long)arg->return_val;
	}
	else
	{
		len = va_arg(ap, int *);
		*len = (int)arg->return_val;
	}
}

void	handle_nflag(va_list ap, t_arg *arg, char **format)
{
	short		*h_len;
	signed char	*hh_len;

	if (arg->h_length == 2)
	{
		hh_len = va_arg(ap, signed char *);
		*hh_len = (signed char)arg->return_val;
	}
	else if (arg->h_length == 1)
	{
		h_len = va_arg(ap, short *);
		*h_len = (short)arg->return_val;
	}
	else
		handle_nlflag(ap, arg);
	(*format)++;
}
