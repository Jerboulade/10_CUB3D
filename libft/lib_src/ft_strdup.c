/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 11:24:38 by jcarere           #+#    #+#             */
/*   Updated: 2021/12/16 21:40:12 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*dup_str;
	char	*tmp;

	tmp = (char *)s1;
	while (*tmp)
		tmp++;
	len = tmp - s1;
	dup_str = (char *)ft_calloc(len + 1, sizeof(char));
	if (!dup_str)
		return (NULL);
	while (*s1)
		*(dup_str++) = *(s1++);
	return (dup_str - len);
}
