/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 15:28:58 by jcarere           #+#    #+#             */
/*   Updated: 2021/12/16 21:37:45 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	i = -1;
	while (++i < len && *src)
		*(dst++) = *(src++);
	i--;
	while (++i < len)
		*dst = 0;
	return (dst);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	size;

	if (!s || !*s)
		return ((char *)ft_calloc(1, sizeof(char)));
	size = ft_strlen(s);
	if (start > size)
		return ((char *)ft_calloc(1, sizeof(char)));
	if (len > size - start)
		len = size - start;
	new = (char *)ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	while (start--)
		s++;
	ft_strncpy(new, s, len);
	new[len] = 0;
	return (new);
}
