/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:52:03 by jcarere           #+#    #+#             */
/*   Updated: 2022/01/15 16:53:11 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	handle_char(va_list ap, t_arg *arg, char **format)
{
	char	c;

	c = va_arg(ap, int);
	if (!arg->just_left)
		ft_putpad(arg->width - 1, arg->zero_flag, arg);
	arg->return_val += write(arg->fd, &c, 1);
	if (arg->just_left)
		ft_putpad(arg->width - 1, 0, arg);
	(*format)++;
}
