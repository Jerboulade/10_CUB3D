/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 17:46:01 by jcarere           #+#    #+#             */
/*   Updated: 2022/08/02 20:30:59 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	format_info_lines(t_list *node)
{
	char	*formated;

	formated = ft_strtrim((char *)node->data, " ");
	if (!formated)
		return (0);
	free(node->data);
	node->data = formated;
	return (1);
}

int	parse_file(t_game *game)
{
	int		ret;
	t_list	*tmp;

	tmp = game->file;
	ret = 0;
	while (tmp && !ret)
	{
		if (game->info->tx->mask < 63)
		{
			if (!format_info_lines(tmp))
				exit_free(game);
			ret = parse_info(game, (char *)tmp->data);
		}
		else
		{
			ret = parse_map(game, tmp);
			break ;
		}
		tmp = tmp->next;
	}
	return (ret);
}
