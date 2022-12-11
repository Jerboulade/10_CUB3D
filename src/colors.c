/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 20:06:45 by jcarere           #+#    #+#             */
/*   Updated: 2022/08/02 20:48:15 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_color(t_game *game, int color[3], int type)
{
	int	hex_color;

	hex_color = (color[0] << 16) + (color[1] << 8) + color[2];
	if (type == FLOOR)
	{
		game->info->tx->floor = hex_color;
		game->info->tx->mask += FLOOR;
	}
	else
	{
		game->info->tx->ceiling = hex_color;
		game->info->tx->mask += CEILING;
	}
}

int	tex_color(t_image *tex, int x, int y)
{
	if (x >= RES || y >= RES)
		return (0);
	return (*(int *)(tex->data + (y * RES + x) * tex->bpp));
}

void	set_pixel_color(t_image *img, int x, int y, int color)
{
	*(int *)(img->data + (y * WIN_W + x) * img->bpp) = color;
}

int	get_tex_color(t_game *game, t_ray *ray)
{
	if (ray->hit_door)
		return (tex_color(game->door_tex, (int)ray->tex.x, (int)ray->tex.y));
	if (ray->hit_side == 1)
	{
		if (ray->dir.y < 0)
			return (tex_color(game->so_tex, (int)ray->tex.x, (int)ray->tex.y));
		else
			return (tex_color(game->no_tex, (int)ray->tex.x, (int)ray->tex.y));
	}
	else
	{
		if (ray->dir.x < 0)
			return (tex_color(game->ea_tex, (int)ray->tex.x, (int)ray->tex.y));
		else
			return (tex_color(game->we_tex, (int)ray->tex.x, (int)ray->tex.y));
	}
}

void	get_floor_pixel(t_game *game, t_ray *r, int x, int y)
{
	if (game->c_tex)
	{
		set_pixel_color(game->shader_tex, x, WIN_H - y - 1, \
			*(int *)(game->shader->data + (y * WIN_W + x) * game->shader->bpp));
		set_pixel_color(game->scene->proj, x, WIN_H - y - 1, \
			tex_color(game->c_tex, r->floor_x, r->floor_y));
	}
	else
	{
		set_pixel_color(game->shader_tex, x, WIN_H - y - 1, 0xff000000);
		set_pixel_color(game->scene->proj, x, WIN_H - y - 1, 0xff000000);
	}
	if (game->f_tex)
	{
		set_pixel_color(game->shader_tex, x, y, \
			*(int *)(game->shader->data + (y * WIN_W + x) * game->shader->bpp));
		set_pixel_color(game->scene->proj, x, y, \
			tex_color(game->f_tex, r->floor_x, r->floor_y));
	}
	else
	{
		set_pixel_color(game->shader_tex, x, y, 0xff000000);
		set_pixel_color(game->scene->proj, x, y, 0xff000000);
	}
}
