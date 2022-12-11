/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:01:20 by jcarere           #+#    #+#             */
/*   Updated: 2022/08/04 17:46:33 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	exit_free(t_game *game)
{
	free_game(game);
	ft_dprintf(STDERR_FILENO, "Error : couldn't allocate memory. Exit\n");
	exit(0);
}

int	head(int ac, char **av)
{
	int		fd;
	int		ret;
	t_game	*game;

	if (ac != 2)
		return (print_error(NULL, ERR_USAGE));
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (print_error(NULL, ERR_NOFILE));
	game = init_game(fd);
	ret = parse_file(game);
	if (ret && !free_game(game))
		return (ret);
	ret = launch_scene(game);
	if (ret && !free_game(game))
		return (ret);
	free_game(game);
	return (0);
}

int	main(int ac, char **av)
{
	int	ret;

	ret = head(ac, av);
	if (ret)
		print_message(ret);
	return (ret);
}
