/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 14:24:36 by jcarere           #+#    #+#             */
/*   Updated: 2022/08/02 20:14:45 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_scene_start_coord(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (game->info->map[++i])
	{
		j = -1;
		while (game->info->map[i][++j])
		{
			if (game->info->map[i][j] == game->info->spawn)
			{
				game->scene->cam.x = (float)j + 0.5;
				game->scene->cam.y = (float)i + 0.5;
				return ;
			}
		}
	}
}

void	get_scene_params(t_game *game)
{
	float	fov_ratio;

	fov_ratio = (float)WIN_W / (2 * WIN_H);
	if (game->info->spawn == 'N')
	{
		set_vector(&game->scene->dir, 0, -1);
		set_vector(&game->scene->plan, fov_ratio, 0);
	}
	else if (game->info->spawn == 'E')
	{
		set_vector(&game->scene->dir, 1, 0);
		set_vector(&game->scene->plan, 0, fov_ratio);
	}
	else if (game->info->spawn == 'S')
	{
		set_vector(&game->scene->dir, 0, 1);
		set_vector(&game->scene->plan, -fov_ratio, 0);
	}
	else if (game->info->spawn == 'W')
	{
		set_vector(&game->scene->dir, -1, 0);
		set_vector(&game->scene->plan, 0, -fov_ratio);
	}
}

int	prepare_images(t_game *g)
{
	g->bg = init_image(g);
	init_background(g->bg, g->info->tx->floor, g->info->tx->ceiling);
	g->shader = init_image(g);
	init_shader(g->shader);
	g->shader_tex = init_image(g);
	g->no_tex = init_texture(g, g->info->tx->no_path);
	g->so_tex = init_texture(g, g->info->tx->so_path);
	g->ea_tex = init_texture(g, g->info->tx->ea_path);
	g->we_tex = init_texture(g, g->info->tx->we_path);
	if (g->info->tx->c_path)
		g->c_tex = init_texture(g, g->info->tx->c_path);
	if (g->info->tx->f_path)
		g->f_tex = init_texture(g, g->info->tx->f_path);
	if (g->info->tx->door_path)
		g->door_tex = init_texture(g, g->info->tx->door_path);
	if (!g->we_tex || !g->no_tex || !g->so_tex || !g->ea_tex \
	|| (g->info->tx->door_path && !g->door_tex) \
	|| (g->info->tx->c_path && !g->c_tex) || (g->info->tx->f_path && !g->f_tex))
		return (print_error(g->info->tx->we_path, ERR_TEX_RES));
	return (0);
}

int	launch_scene(t_game *game)
{
	int	ret;

	game->mlx_ptr = mlx_init();
	if (!game->mlx_ptr)
		exit_free(game);
	game->win_ptr = mlx_new_window(game->mlx_ptr, WIN_W, WIN_H, "cub3D");
	if (!game->win_ptr)
		exit_free(game);
	ret = prepare_images(game);
	if (ret)
		return (ret);
	game->scene = ft_calloc(1, sizeof(*game->scene));
	if (!game->scene)
		exit_free(game);
	game->scene->proj = init_image(game);
	get_scene_start_coord(game);
	get_scene_params(game);
	render(game);
	mlx_hook(game->win_ptr, ON_KEYDOWN, 0, event, game);
	mlx_loop(game->mlx_ptr);
	return (0);
}
