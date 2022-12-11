/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 20:11:01 by jcarere           #+#    #+#             */
/*   Updated: 2022/08/02 20:14:05 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move(t_game *game, float step_x, float step_y)
{
	char	next;
	char	**map;

	map = game->info->map;
	next = map[(int)game->scene->cam.y][(int)(game->scene->cam.x + step_x)];
	if (next != '1' && next != 'D')
		game->scene->cam.x += step_x;
	next = map[(int)(game->scene->cam.y + step_y)][(int)game->scene->cam.x];
	if (next != '1' && next != 'D')
		game->scene->cam.y += step_y;
}

void	rotate(t_scene *pos, float speed)
{
	float	tmp;

	tmp = pos->dir.x;
	pos->dir.x = pos->dir.x * cos(speed) - pos->dir.y * sin(speed);
	pos->dir.y = tmp * sin(speed) + pos->dir.y * cos(speed);
	tmp = pos->plan.x;
	pos->plan.x = pos->plan.x * cos(speed) - pos->plan.y * sin(speed);
	pos->plan.y = tmp * sin(speed) + pos->plan.y * cos(speed);
}

int	event(int key, t_game *game)
{
	if (key == ESC_KEY)
		exit(free_game(game) != NULL);
	if (key == SPACE)
		check_action(game);
	if (key == Z_KEY)
		move(game, game->scene->dir.x * SPEED, game->scene->dir.y * SPEED);
	else if (key == Q_KEY)
		move(game, -game->scene->plan.x * SPEED, -game->scene->plan.y * SPEED);
	else if (key == S_KEY)
		move(game, -game->scene->dir.x * SPEED, -game->scene->dir.y * SPEED);
	else if (key == D_KEY)
		move(game, game->scene->plan.x * SPEED, game->scene->plan.y * SPEED);
	else if (key == LEFT_KEY)
		rotate(game->scene, -SPEED / 2);
	else if (key == RIGHT_KEY)
		rotate(game->scene, SPEED / 2);
	game->radar = detect_tile(game);
	render(game);
	print_action(game);
	return (0);
}
