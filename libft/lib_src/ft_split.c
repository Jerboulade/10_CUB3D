/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 20:46:15 by jcarere           #+#    #+#             */
/*   Updated: 2021/12/16 22:09:37 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strrep(char *str, char c, char rep)
{
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == c)
			*(str) = rep;
		str++;
	}
	return (str);
}

static void	*ft_free_tab(char **tab, size_t nb_tab)
{
	size_t	i;

	if (!tab)
		return (NULL);
	i = 0;
	while (tab[i] && i < nb_tab)
		free(tab[i++]);
	free(tab);
	return (NULL);
}

static size_t	ft_count_word(const char *str, size_t len)
{
	char			*tmp;
	size_t			words;
	unsigned char	on_w;

	tmp = (char *)str;
	words = 0;
	on_w = 0;
	while (tmp < (str + len))
	{
		if (*tmp && !on_w && ++words)
			on_w = 1;
		else if (!*tmp && on_w)
			on_w = 0;
		tmp++;
	}
	return (words);
}

static char	**fill_tab(char **res, char *s_dup, size_t nb_word)
{
	int		i;
	size_t	word_max;
	char	*tmp;

	i = 0;
	tmp = s_dup;
	word_max = nb_word;
	while (nb_word > 0)
	{
		while (!*tmp)
			tmp++;
		res[i] = ft_strdup(tmp);
		if (!res[i])
		{
			free(s_dup);
			return (ft_free_tab(res, word_max));
		}
		while (*tmp)
			tmp++;
		i++;
		nb_word--;
	}
	res[i] = NULL;
	free(s_dup);
	return (res);
}

char	**ft_split(char const *s, char c)
{
	size_t		nb_word;
	char		**res;
	char		*s_dup;
	char		*tmp;

	if (!s)
		return (NULL);
	s_dup = ft_strdup(s);
	if (!s_dup)
		return (NULL);
	tmp = ft_strrep(s_dup, c, 0);
	nb_word = ft_count_word(s_dup, tmp - s_dup);
	if (!nb_word)
	{
		free(s_dup);
		return ((char **)ft_calloc(1, sizeof(char *)));
	}
	res = (char **)ft_calloc(nb_word + 1, sizeof(char *));
	if (!res)
		return (NULL);
	return (fill_tab(res, s_dup, nb_word));
}
