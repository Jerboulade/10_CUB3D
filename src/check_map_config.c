/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_config.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/24 17:52:39 by jcarere           #+#    #+#             */
/*   Updated: 2022/08/02 20:49:04 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_east_and_west_pos(char *line, int j, int len)
{
	if (j && !is_space_or_one(line[j - 1]))
		return (1);
	if (j < len - 1 && !is_space_or_one(line[j + 1]))
		return (1);
	return (0);
}

int	check_north_pos(t_game *game, int i, int j, int len)
{
	if (!i)
		return (0);
	if (!is_space_or_one(game->info->map[i - 1][j]))
		return (1);
	if (check_east_and_west_pos(game->info->map[i - 1], j, len))
		return (1);
	return (0);
}

int	check_south_pos(t_game *game, int i, int j, int len)
{
	if (i == game->info->line - 1)
		return (0);
	if (!is_space_or_one(game->info->map[i + 1][j]))
		return (1);
	if (check_east_and_west_pos(game->info->map[i + 1], j, len))
		return (1);
	return (0);
}

int	check_pos(t_game *game, int i, int j, int len)
{
	return (check_east_and_west_pos(game->info->map[i], j, len) \
		|| check_north_pos(game, i, j, len) \
		|| check_south_pos(game, i, j, len));
}

int	check_map_config(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->info->map[++i])
	{
		j = -1;
		while (game->info->map[i][++j])
		{
			if (!is_valid_char(game, game->info->map[i][j]))
				return (print_error_map(game, i, j, ERR_INVALID_CHAR));
			else if (is_spawn_char(game->info->map[i][j]) && game->info->spawn)
				return (print_error_map(game, i, j, ERR_MULT_SPAWN));
			else if (is_spawn_char(game->info->map[i][j]))
				game->info->spawn = game->info->map[i][j];
			else if ((!i || i == game->info->line - 1) \
			&& !is_space_or_one(game->info->map[i][j]))
				return (print_error_map(game, i, j, ERR_MISCONFIG));
			else if (game->info->map[i][j] == ' ' \
			&& check_pos(game, i, j, game->info->col))
				return (print_error_map(game, i, j, ERR_MISCONFIG));
		}
	}
	return (0);
}
