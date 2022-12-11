/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 03:49:56 by jcarere           #+#    #+#             */
/*   Updated: 2021/12/28 03:50:08 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	int					neg;
	unsigned long long	res;
	int					i;
	int					len;

	res = 0;
	i = 0;
	neg = 1;
	len = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\v' || \
	str[i] == '\n' || str[i] == '\r' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
		neg = 1 - ((str[i++] == '-') * 2);
	while (str[i] >= '0' && str[i] <= '9' && ++len)
		res = (res * 10) + str[i++] - '0';
	if (res > LONG_MAX || len > 19)
		return (0 - (neg > 0));
	return (res * neg);
}
