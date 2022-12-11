/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:46:20 by jcarere           #+#    #+#             */
/*   Updated: 2022/08/02 20:39:46 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_vector(t_vector2 *vector, float x, float y)
{
	vector->x = x;
	vector->y = y;
}

int	print_error_map(t_game *game, int i_err, int j_err, int ret)
{
	int		i;
	int		j;
	char	**map;

	i = -1;
	map = game->info->map;
	while (map[++i])
	{
		ft_printf("%s|%s", ORANGE, RESET);
		if (i <= i_err)
			ft_printf("%s", CYAN);
		j = -1;
		while (map[i][++j])
		{
			if (i == i_err && j == j_err && map[i][j] == ' ')
				ft_printf("%s %s", BG_ORANGE, RESET);
			else if (i == i_err && j == j_err && map[i][j] != ' ')
				ft_printf("%s%c%s", ORANGE, map[i][j], RESET);
			else
				ft_printf("%c", map[i][j]);
		}
		ft_printf("%s|\n", ORANGE);
	}
	ft_printf("%s\n", RESET);
	return (print_error(NULL, ret));
}

int	print_message(int ret)
{
	if (errno)
		return (errno);
	if (ret == ERR_USAGE)
		ft_dprintf(STDERR_FILENO, "usage: ./cub3D path_to_file.cub\n");
	else if (ret == ERR_TEX_RES)
		ft_dprintf(STDERR_FILENO, "Resolution sould be %dx%d\n", RES, RES);
	else if (ret == ERR_INVALID)
		ft_dprintf(STDERR_FILENO, "Invalid information line\n");
	else if (ret == ERR_INVALID_COLOR)
		ft_dprintf(STDERR_FILENO, "Invalid color\n");
	else if (ret == ERR_DUP)
		ft_dprintf(STDERR_FILENO, "Duplicate information\n");
	else if (ret == ERR_MAP_EMPTY_LINE)
		ft_dprintf(STDERR_FILENO, "Map contains empty line\n");
	else if (ret == ERR_INVALID_CHAR)
		ft_dprintf(STDERR_FILENO, "Map contains invalid character\n");
	else if (ret == ERR_MULT_SPAWN)
		ft_dprintf(STDERR_FILENO, "Map contains multiple spawn points\n");
	else if (ret == ERR_INVALID_MAP)
		ft_dprintf(STDERR_FILENO, "Invalid map size OR no spawn point\n");
	else if (ret == ERR_MISCONFIG)
		ft_dprintf(STDERR_FILENO, "Invalid map configuration\n");
	else if (ret == ERR_TEX_FORMAT)
		ft_dprintf(STDERR_FILENO, "Texture file format must be '.xpm'\n");
	return (ret);
}

int	print_error(char *obj, int ret_val)
{
	ft_dprintf(STDERR_FILENO, "%sError: ", ORANGE);
	if (obj)
		ft_dprintf(STDERR_FILENO, "'%s%s%s' : ", MAG, obj, ORANGE);
	ft_dprintf(STDERR_FILENO, "%s", RESET);
	if (errno)
		ft_dprintf(STDERR_FILENO, "%s\n", strerror(errno));
	return (ret_val);
}

int	is_space_or_one(char c)
{
	return (c == ' ' || c == '1');
}
