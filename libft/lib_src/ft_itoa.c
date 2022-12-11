/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 18:27:10 by jcarere           #+#    #+#             */
/*   Updated: 2021/12/16 23:42:57 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	n_size(int n)
{
	int	size;

	size = 1;
	if (n < 0)
		size++;
	while ((n / 10) && size++)
		n /= 10;
	return (size);
}

char	*ft_itoa(int n)
{
	char	neg;
	char	len;
	char	*res;

	if (!n)
		return (ft_strdup("0"));
	else if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 2147483647)
		return (ft_strdup("2147483647"));
	neg = (n < 0);
	len = n_size(n);
	res = (char *)ft_calloc((len + 1), sizeof(char));
	if (!res)
		return (NULL);
	res[0] = 0 + ((n < 0) * 45);
	while (len-- > neg)
	{
		res[(int)len] = ((n * (1 - ((n < 0) * 2))) % 10) + '0';
		n /= 10;
	}
	return (res);
}
