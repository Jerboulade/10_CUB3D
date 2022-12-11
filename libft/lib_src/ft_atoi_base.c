/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:10:22 by jcarere           #+#    #+#             */
/*   Updated: 2021/12/16 22:42:27 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_space(char c)
{
	if ((c == ' ' || c == '\t' || c == '\v' || \
	c == '\n' || c == '\r' || c == '\f'))
		return (1);
	return (0);
}

static int	check_base(char *b)
{
	int	len;
	int	i;
	int	j;

	if (!b)
		return (0);
	len = 0;
	while (b[len])
		len++;
	if (len <= 1)
		return (0);
	i = -1;
	while (++i < len)
	{
		j = -1;
		while (++j < len)
		{
			if ((i != j && b[i] == b[j]) || b[j] == '+' || b[j] == '-' || \
			is_space(b[j]))
				return (0);
		}
	}
	return (len);
}

static int	is_base(char c, char *base)
{
	int	i;

	i = -1;
	while (base[++i])
	{
		if (c == base[i])
			return (1);
	}
	return (0);
}

static int	base_index(char c, char *base)
{
	int	i;

	i = 0;
	while (c != base[i])
		i++;
	return (i);
}

int	ft_atoi_base(char *str, char *base)
{
	int			neg;
	long long	res;
	int			i;
	int			b;

	res = 0;
	i = 0;
	neg = 1;
	b = check_base(base);
	if (!b)
		return (0);
	while (is_space(str[i]))
		i++;
	while (str[i] == '+' || str[i] == '-')
		neg *= 1 - ((str[i++] == '-') * 2);
	while (is_base(str[i], base))
		res = (res * b) + base_index(str[i++], base);
	return (res * neg);
}
