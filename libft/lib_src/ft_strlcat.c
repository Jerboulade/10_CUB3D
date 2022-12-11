/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 16:47:27 by jcarere           #+#    #+#             */
/*   Updated: 2021/12/16 21:38:52 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i_dst;
	size_t	src_len;
	size_t	tot;
	size_t	i;

	i_dst = ft_strlen(dst);
	src_len = ft_strlen(src);
	tot = i_dst + src_len;
	i = 0;
	if (i_dst >= dstsize)
		return (dstsize + src_len);
	while (src[i] && i_dst < dstsize - 1)
		dst[i_dst++] = src[i++];
	dst[i_dst] = 0;
	return (tot);
}
