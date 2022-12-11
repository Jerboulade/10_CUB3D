/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 23:27:57 by jcarere           #+#    #+#             */
/*   Updated: 2022/08/02 20:48:39 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	parse_color(t_game *game, char *sequence, int type)
{
	int		length;
	int		color[3];
	char	**rgb_tab;

	rgb_tab = ft_split(sequence, ',');
	length = 0;
	while (rgb_tab[length])
		length++;
	if (length != 3)
	{
		free_tab(rgb_tab);
		return (print_error(sequence, ERR_INVALID_COLOR));
	}
	color[0] = ft_atoi(rgb_tab[0]);
	color[1] = ft_atoi(rgb_tab[1]);
	color[2] = ft_atoi(rgb_tab[2]);
	if (!is_valid_color(color))
	{
		free_tab(rgb_tab);
		return (print_error(sequence, ERR_INVALID_COLOR));
	}
	set_color(game, color, type);
	free_tab(rgb_tab);
	return (0);
}

int	set_texture(t_game *game, int type, char *cur_line, char *path)
{
	int		ret;
	char	*ptr;

	ret = is_existing_texture(path);
	if (ret)
		return (ret);
	ptr = ft_strnstr(cur_line, path, ft_strlen(cur_line));
	if (type == NO)
		game->info->tx->no_path = ptr;
	else if (type == SO)
		game->info->tx->so_path = ptr;
	else if (type == EA)
		game->info->tx->ea_path = ptr;
	else if (type == WE)
		game->info->tx->we_path = ptr;
	else if (type == FLOOR)
		game->info->tx->f_path = ptr;
	else if (type == CEILING)
		game->info->tx->c_path = ptr;
	else
		game->info->tx->door_path = ptr;
	game->info->tx->mask += type;
	return (0);
}

int	check_duplicate_for_pretty_message(t_game *game, char *elem)
{
	if ((game->info->tx->mask & NO) && ft_strequ("NO", elem))
		return (222);
	else if ((game->info->tx->mask & SO) && ft_strequ("SO", elem))
		return (222);
	else if ((game->info->tx->mask & EA) && ft_strequ("EA", elem))
		return (222);
	else if ((game->info->tx->mask & WE) && ft_strequ("WE", elem))
		return (222);
	else if ((game->info->tx->mask & FLOOR) && \
	(ft_strequ("F", elem) || ft_strequ("PF", elem)))
		return (222);
	else if ((game->info->tx->mask & CEILING) && \
	(ft_strequ("C", elem) || ft_strequ("PC", elem)))
		return (222);
	return (0);
}

int	check_texture(t_game *game, char *cur_line, char **tab)
{
	int	ret;

	if (check_duplicate_for_pretty_message(game, tab[0]) == 222)
		return (print_error(cur_line, ERR_DUP));
	else if (!(game->info->tx->mask & NO) && ft_strequ("NO", tab[0]))
		ret = set_texture(game, NO, cur_line, tab[1]);
	else if (!(game->info->tx->mask & SO) && ft_strequ("SO", tab[0]))
		ret = set_texture(game, SO, cur_line, tab[1]);
	else if (!(game->info->tx->mask & EA) && ft_strequ("EA", tab[0]))
		ret = set_texture(game, EA, cur_line, tab[1]);
	else if (!(game->info->tx->mask & WE) && ft_strequ("WE", tab[0]))
		ret = set_texture(game, WE, cur_line, tab[1]);
	else if (!(game->info->tx->mask & FLOOR) && ft_strequ("F", tab[0]))
		ret = parse_color(game, tab[1], FLOOR);
	else if (!(game->info->tx->mask & FLOOR) && ft_strequ("PF", tab[0]))
		ret = set_texture(game, FLOOR, cur_line, tab[1]);
	else if (!(game->info->tx->mask & CEILING) && ft_strequ("C", tab[0]))
		ret = parse_color(game, tab[1], CEILING);
	else if (!(game->info->tx->mask & CEILING) && ft_strequ("PC", tab[0]))
		ret = set_texture(game, CEILING, cur_line, tab[1]);
	else if (ft_strequ("DOOR", tab[0]))
		ret = set_texture(game, 0, cur_line, tab[1]);
	else
		return (print_error(cur_line, ERR_INVALID));
	return (ret);
}

int	parse_info(t_game *game, char *cur_line)
{
	int		i;
	int		ret;
	char	**tab;

	if (is_empty_line(cur_line))
		return (0);
	ret = 0;
	tab = ft_split(cur_line, ' ');
	if (!tab)
		exit_free(game);
	i = 0;
	while (tab[i])
		i++;
	if (i != 2)
		ret = print_error(cur_line, ERR_INVALID);
	if (!ret)
		ret = check_texture(game, cur_line, tab);
	free_tab(tab);
	return (ret);
}
