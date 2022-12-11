/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 20:10:06 by jcarere           #+#    #+#             */
/*   Updated: 2022/08/02 20:14:03 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	detect_tile(t_game *game)
{
	int	x;
	int	y;

	x = (int)(game->scene->cam.x + game->scene->dir.x);
	y = (int)(game->scene->cam.y + game->scene->dir.y);
	return (game->info->map[y][x]);
}

void	modify_detection(t_game *game, char new)
{
	int	x;
	int	y;

	x = (int)(game->scene->cam.x + game->scene->dir.x);
	y = (int)(game->scene->cam.y + game->scene->dir.y);
	game->info->map[y][x] = new;
}

void	check_action(t_game *game)
{
	if (game->radar == 'D')
		modify_detection(game, 'd');
	else if (game->radar == 'd')
		modify_detection(game, 'D');
}

void	print_action(t_game *game)
{
	if (game->radar == 'D')
		mlx_string_put(game->mlx_ptr, game->win_ptr, \
		WIN_W >> 1, WIN_HH, WHITE, "Open door");
	else if (game->radar == 'd')
		mlx_string_put(game->mlx_ptr, game->win_ptr, \
		WIN_W >> 1, WIN_HH, WHITE, "Close door");
}
