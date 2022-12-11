/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:44:12 by jcarere           #+#    #+#             */
/*   Updated: 2022/08/04 16:00:46 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

void	free_info(t_info *info)
{
	if (!info)
		return ;
	if (info->map)
		free(info->map);
	if (info->tx)
		free(info->tx);
	free(info);
}

void	free_image(t_game *game, t_image *img)
{
	if (img)
	{
		mlx_destroy_image(game->mlx_ptr, img->ptr);
		free(img);
	}
}

void	free_scene(t_game *game, t_scene *scene)
{
	free_image(game, scene->proj);
	free(scene);
}

void	*free_game(t_game *game)
{
	if (!game)
		return (NULL);
	if (game->file)
		ft_lstclear(&game->file, &free);
	if (game->info)
		free_info(game->info);
	if (game->scene)
		free_scene(game, game->scene);
	free_image(game, game->bg);
	free_image(game, game->shader);
	free_image(game, game->shader_tex);
	free_image(game, game->no_tex);
	free_image(game, game->so_tex);
	free_image(game, game->ea_tex);
	free_image(game, game->we_tex);
	free_image(game, game->c_tex);
	free_image(game, game->f_tex);
	free_image(game, game->door_tex);
	if (game->mlx_ptr && game->win_ptr)
		mlx_destroy_window(game->mlx_ptr, game->win_ptr);
	free(game);
	return (NULL);
}
