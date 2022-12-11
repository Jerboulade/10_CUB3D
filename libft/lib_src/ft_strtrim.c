/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 17:41:03 by jcarere           #+#    #+#             */
/*   Updated: 2021/12/16 21:37:32 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isequalset(char c, char const *set)
{
	if (!set)
		return (0);
	while (*set)
	{
		if (c == *(set++))
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*tmp;
	char	*trim;
	size_t	len;

	if (!s1)
		return (NULL);
	while (ft_isequalset(*s1, set))
		s1++;
	tmp = (char *)s1;
	while (*tmp)
		tmp++;
	tmp--;
	while (ft_isequalset(*tmp, set))
		tmp--;
	tmp++;
	len = tmp - s1;
	if (s1 >= tmp)
		return ((char *)ft_calloc(1, sizeof(char)));
	trim = (char *)ft_calloc(len + 1, sizeof(char));
	if (!trim)
		return (NULL);
	while (s1 != tmp)
		*(trim++) = *(s1++);
	return (trim - len);
}
