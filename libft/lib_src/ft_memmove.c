/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 17:50:47 by jcarere           #+#    #+#             */
/*   Updated: 2021/12/16 21:38:31 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	tmp_dst = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	if ((!src && !dst && len) || (dst == src))
		return (dst);
	if (tmp_src < tmp_dst && tmp_src + len > tmp_dst)
	{
		while (len--)
			*(tmp_dst + len) = *(tmp_src + len);
	}
	else
	{
		while (len--)
			*(tmp_dst++) = *(tmp_src++);
	}
	return (dst);
}
