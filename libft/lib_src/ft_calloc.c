/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 10:42:06 by jcarere           #+#    #+#             */
/*   Updated: 2021/12/16 21:39:28 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void			*area;
	size_t			r;
	unsigned char	*tmp;

	r = count * size;
	area = (void *)malloc(r);
	if (!area)
		return (NULL);
	tmp = area;
	while (r--)
		*(tmp++) = 0;
	return (area);
}
