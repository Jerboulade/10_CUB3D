/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:52:52 by jcarere           #+#    #+#             */
/*   Updated: 2022/01/15 17:11:43 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putpad(int len, char zero, t_arg *arg)
{
	if (len <= 0)
		return ;
	arg->return_val += len;
	if (zero)
	{
		while (--len >= 0)
			write(arg->fd, "0", 1);
	}
	else
	{
		while (--len >= 0)
			write(arg->fd, " ", 1);
	}
}
