/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 20:08:15 by jcarere           #+#    #+#             */
/*   Updated: 2022/08/04 15:44:27 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_floor_dist(t_ray *r)
{
	if (r->hit_side == 0 && r->dir.x > 0)
		set_vector(&r->floor_dist, r->cast.x, r->cast.y + r->wall_x);
	else if (r->hit_side == 0 && r->dir.x < 0)
		set_vector(&r->floor_dist, r->cast.x + 1.0, r->cast.y + r->wall_x);
	else if (r->hit_side == 1 && r->dir.y > 0)
		set_vector(&r->floor_dist, r->cast.x + r->wall_x, r->cast.y);
	else
		set_vector(&r->floor_dist, r->cast.x + r->wall_x, r->cast.y + 1.0);
}

void	get_floor_coord(t_ray *ray, int y)
{
	float		step;
	t_vector2	dist;

	step = (float)WIN_H / (2 * y - WIN_H) / ray->dist;
	dist.x = (step * ray->floor_dist.x) + ((1.0 - step) * ray->pos.x);
	dist.y = (step * ray->floor_dist.y) + ((1.0 - step) * ray->pos.y);
	ray->floor_x = (int)(dist.x * RES) % RES;
	ray->floor_y = (int)(dist.y * RES) % RES;
}

void	get_colomn_param(t_ray *r)
{
	if (r->hit_side == 0)
		r->dist = fabs((r->cast.x - r->pos.x + (1 - r->step.x) / 2) / r->dir.x);
	else
		r->dist = fabs((r->cast.y - r->pos.y + (1 - r->step.y) / 2) / r->dir.y);
	r->col_h = fabs(WIN_H / r->dist);
	r->col_start = (-r->col_h / 2) + WIN_HH;
	r->col_end = (r->col_h / 2) + WIN_HH;
	if (r->hit_side == 1)
		r->wall_x = r->pos.x + \
		((r->cast.y - r->pos.y + (1 - r->step.y) / 2) / r->dir.y) * r->dir.x;
	else
		r->wall_x = r->pos.y + \
		((r->cast.x - r->pos.x + (1 - r->step.x) / 2) / r->dir.x) * r->dir.y;
	r->wall_x = r->wall_x - (int)r->wall_x;
	r->tex.x = r->wall_x * RES;
	if ((!r->hit_side && r->dir.x > 0) || (r->hit_side && r->dir.y < 0))
		r->tex.x = RES - r->tex.x - 1;
}

void	cast_ray(t_game *game, t_ray *ray)
{
	while (1)
	{
		if (ray->size.x < ray->size.y)
		{
			ray->size.x += ray->delta.x;
			ray->cast.x += ray->step.x;
			ray->hit_side = 0;
		}
		else
		{
			ray->size.y += ray->delta.y;
			ray->cast.y += ray->step.y;
			ray->hit_side = 1;
		}
		if (game->info->map[(int)ray->cast.y][(int)ray->cast.x] == '1')
			break ;
		if (game->info->map[(int)ray->cast.y][(int)ray->cast.x] == 'D')
		{
			ray->hit_door = 1;
			break ;
		}
	}
}

void	get_ray_size(t_ray *ray)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->size.x = (ray->pos.x - ray->cast.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->size.x = (ray->cast.x + 1.0 - ray->pos.x) * ray->delta.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->size.y = (ray->pos.y - ray->cast.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->size.y = (ray->cast.y + 1.0 - ray->pos.y) * ray->delta.y;
	}
}
