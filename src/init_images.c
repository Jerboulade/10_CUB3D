/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 20:12:47 by jcarere           #+#    #+#             */
/*   Updated: 2022/08/02 20:14:07 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_background(t_image *bg, int floor, int ceiling)
{
	int	i;
	int	*data;

	data = (int *)bg->data;
	i = -1;
	while (++i < (WIN_H * WIN_W >> 1))
		data[i] = ceiling;
	while (i < (WIN_H * WIN_W))
		data[i++] = floor;
}

void	init_shader(t_image *shader)
{
	int	i;
	int	*data;

	data = (int *)shader->data;
	shader->endian = 255;
	i = -1;
	while (++i < (WIN_H * WIN_W >> 1))
	{
		if (!(i % shader->size_line))
			shader->endian -= 2;
		data[i] = shader->endian << 24;
	}
	while (i < WIN_H * WIN_W)
	{
		if (!(i % shader->size_line))
			shader->endian += 2;
		data[i++] = shader->endian << 24;
	}
}

t_image	*init_image(t_game *game)
{
	t_image	*i;

	i = ft_calloc(1, sizeof(*i));
	if (!i)
		exit_free(game);
	i->ptr = mlx_new_image(game->mlx_ptr, WIN_W, WIN_H);
	i->data = mlx_get_data_addr(i->ptr, &i->bpp, &i->size_line, &i->endian);
	i->bpp /= 8;
	return (i);
}

t_image	*init_texture(t_game *game, char *path)
{
	t_image	*i;
	int		h;
	int		w;

	errno = 0;
	i = ft_calloc(1, sizeof(*i));
	if (!i)
		exit_free(game);
	i->ptr = mlx_xpm_file_to_image(game->mlx_ptr, path, &h, &w);
	i->data = mlx_get_data_addr(i->ptr, &i->bpp, &i->size_line, &i->endian);
	i->bpp /= 8;
	if (h != RES || w != RES)
		return (NULL);
	return (i);
}
