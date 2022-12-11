/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 17:34:47 by jcarere           #+#    #+#             */
/*   Updated: 2021/12/17 00:35:41 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		needle_len;

	if (!*needle)
		return ((char *)haystack);
	needle_len = ft_strlen(needle);
	while (*haystack && (len >= needle_len))
	{
		if (*haystack == *needle)
		{
			if (!(ft_strncmp(haystack, needle, needle_len)))
				return ((char *)haystack);
		}
		haystack++;
		len--;
	}
	return (NULL);
}
