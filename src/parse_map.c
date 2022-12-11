/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 23:27:52 by jcarere           #+#    #+#             */
/*   Updated: 2022/08/02 20:32:38 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	built_map_tab(t_game *game, t_list *start, int i)
{
	size_t	len;
	char	*tmp;

	game->info->map = ft_calloc(game->info->line + 1, sizeof(*game->info->map));
	if (!game->info->map)
		exit_free(game);
	while (start)
	{
		len = ft_strlen((char *)start->data);
		tmp = ft_calloc(game->info->col + 3, sizeof(*tmp));
		if (!tmp)
			exit_free(game);
		tmp[0] = ' ';
		ft_memcpy(tmp + 1, (char *)start->data, len);
		ft_memset(tmp + len + 1, ' ', game->info->col - len + 1);
		free(start->data);
		start->data = tmp;
		game->info->map[i++] = tmp;
		start = start->next;
	}
}

int	check_line_size(t_game *game, char *line)
{
	int		length;
	char	*start;

	start = line;
	if (is_empty_line(line))
		return (1);
	while (*line)
	{
		if (is_spawn_char(*line))
			game->info->spawn = *line;
		line++;
	}
	length = line - start;
	if (length > game->info->col)
		game->info->col = length;
	game->info->line++;
	return (0);
}

void	remove_trailing_space(char *line)
{
	char	*start;

	start = line;
	while (*line)
		line++;
	while (line > start)
	{
		line--;
		if (*line != ' ')
		{
			*(line + 1) = 0;
			break ;
		}
	}
}

int	parse_map(t_game *game, t_list *start)
{
	t_list	*current;

	while (start && is_empty_line((char *)start->data))
		start = start->next;
	current = start;
	while (current)
	{
		remove_trailing_space((char *)current->data);
		if (check_line_size(game, (char *)current->data))
			return (print_error(NULL, ERR_MAP_EMPTY_LINE));
		current = current->next;
	}
	if (game->info->col < 3 || game->info->line < 3 || !game->info->spawn)
		return (print_error(NULL, ERR_INVALID_MAP));
	built_map_tab(game, start, 0);
	game->info->spawn = 0;
	return (check_map_config(game));
}
