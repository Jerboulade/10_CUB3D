/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 15:59:45 by jcarere           #+#    #+#             */
/*   Updated: 2021/01/07 02:21:38 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	char	*tmp_src;

	tmp_src = (char *)src;
	src_len = 0;
	while (src[src_len])
		src_len++;
	if (!dstsize)
		return (src_len);
	while (*tmp_src && ((size_t)(tmp_src - src)) < (dstsize - 1))
		*(dst++) = *(tmp_src++);
	*dst = 0;
	return (src_len);
}
