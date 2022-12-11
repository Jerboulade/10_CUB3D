/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 20:09:11 by jcarere           #+#    #+#             */
/*   Updated: 2022/08/02 20:14:01 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render_colomn(t_game *game, t_ray *r, int x)
{
	int	y;
	int	shade;

	shade = (255 - (int)r->dist * 10);
	if (shade < 0)
		shade = 0;
	else
		shade <<= 24;
	y = -1;
	while (++y < WIN_H - 1)
	{
		r->tex.y = ((y * 2 - WIN_H + (r->col_h)) * (RES >> 1) / (r->col_h));
		if (y >= r->col_start && y <= r->col_end)
		{
			set_pixel_color(game->shader_tex, x, y, shade);
			set_pixel_color(game->scene->proj, x, y, get_tex_color(game, r));
		}
		else if (y > r->col_end)
		{
			if (game->c_tex || game->f_tex)
				get_floor_coord(r, y);
			get_floor_pixel(game, r, x, y);
		}
	}
}

void	ray_cast(t_game *game, int x)
{
	float	col_pos;
	t_ray	ray;

	ray.hit_door = 0;
	col_pos = (2 * (float)x / WIN_W) - 1;
	ray.pos.x = game->scene->cam.x;
	ray.pos.y = game->scene->cam.y;
	ray.dir.x = game->scene->dir.x + game->scene->plan.x * col_pos;
	ray.dir.y = game->scene->dir.y + game->scene->plan.y * col_pos;
	ray.cast.x = (int)ray.pos.x;
	ray.cast.y = (int)ray.pos.y;
	ray.delta.x = sqrtf(1 + (ray.dir.y * ray.dir.y) / (ray.dir.x * ray.dir.x));
	ray.delta.y = sqrtf(1 + (ray.dir.x * ray.dir.x) / (ray.dir.y * ray.dir.y));
	get_ray_size(&ray);
	cast_ray(game, &ray);
	get_colomn_param(&ray);
	if (game->c_tex || game->f_tex)
		get_floor_dist(&ray);
	render_colomn(game, &ray, x);
	ray.hit_door = 0;
}

void	render(t_game *g)
{
	int	i;

	i = -1;
	while (++i <= WIN_W)
		ray_cast(g, i);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->bg->ptr, 0, 0);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->shader->ptr, 0, 0);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->scene->proj->ptr, 0, 0);
	mlx_put_image_to_window(g->mlx_ptr, g->win_ptr, g->shader_tex->ptr, 0, 0);
}
