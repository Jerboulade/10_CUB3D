/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:44:09 by jcarere           #+#    #+#             */
/*   Updated: 2022/08/02 20:42:39 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_list	*get_file(int fd, t_list *lst)
{
	t_list	*tmp;
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		*ft_strchr(line, '\n') = 0;
		if (!lst)
		{
			lst = ft_lstnew(line);
			if (!lst)
				return (NULL);
			tmp = lst;
		}
		else
		{
			tmp->next = ft_lstnew(line);
			if (!tmp->next)
				return (NULL);
			tmp = tmp->next;
		}
	}
	return (lst);
}

t_game	*init_game(int fd)
{
	t_game	*game;

	game = ft_calloc(1, sizeof(*game));
	if (!game)
		exit_free(game);
	game->info = ft_calloc(1, sizeof(*game->info));
	if (!game->info)
		exit_free(game);
	game->file = get_file(fd, NULL);
	if (!game->file)
		exit_free(game);
	game->info->tx = ft_calloc(1, sizeof(*game->info->tx));
	if (!game->info->tx)
		exit_free(game);
	return (game);
}
