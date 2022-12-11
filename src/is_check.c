/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 20:36:13 by jcarere           #+#    #+#             */
/*   Updated: 2022/08/02 20:36:42 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_spawn_char(char c)
{
	return (c == 'N' || c == 'S' \
			|| c == 'E' || c == 'W');
}

int	is_valid_char(t_game *game, char c)
{
	return (c == ' ' || c == '0' || c == '1' \
			|| c == 'N' || c == 'S' \
			|| c == 'E' || c == 'W' || (c == 'D' && game->info->tx->door_path));
}

int	is_valid_color(int color[3])
{
	return (color[0] >= 0 && color[0] <= 255 \
		&& color[1] >= 0 && color[1] <= 255 \
		&& color[2] >= 0 && color[2] <= 255);
}

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ')
			return (0);
		line++;
	}
	return (1);
}

int	is_existing_texture(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (print_error(path, ERR_NOFILE));
	close(fd);
	if (!ft_strequ(".xpm", ft_strrchr(path, '.')))
		return (print_error(path, ERR_TEX_FORMAT));
	return (0);
}
