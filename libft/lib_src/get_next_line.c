/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 16:08:30 by jcarere           #+#    #+#             */
/*   Updated: 2021/12/16 22:37:20 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*extract_line(t_stock **stock_fd)
{
	char	*line;
	char	*tmp;

	line = NULL;
	if (!(*(*stock_fd)->line_end))
	{
		line = ft_strdup((*stock_fd)->line_start);
		if (!line)
			return (NULL);
		free((*stock_fd)->buff);
		free((*stock_fd)->begin);
		free(*stock_fd);
		*stock_fd = NULL;
		return (line);
	}
	*(*stock_fd)->line_end = 0;
	line = ft_strdup((*stock_fd)->line_start);
	tmp = ft_strjoin(line, "\n");
	if (!line || !tmp)
		return (NULL);
	free(line);
	(*stock_fd)->line_start = ++(*stock_fd)->line_end;
	return (tmp);
}

static int	join_buff(t_stock **stock_fd, int size)
{
	char	*tmp;

	(*stock_fd)->buff[size] = 0;
	tmp = ft_strjoin((*stock_fd)->line_start, (*stock_fd)->buff);
	if (!tmp)
		return (0);
	free((*stock_fd)->begin);
	(*stock_fd)->begin = tmp;
	(*stock_fd)->line_start = tmp;
	return (1);
}

static int	init_stock(t_stock **stock_fd)
{
	*stock_fd = (t_stock *)ft_calloc(1, sizeof(t_stock));
	if (!(*stock_fd))
		return (0);
	(*stock_fd)->buff = (char *)malloc((BUFF_SIZE + 1) * sizeof(char));
	if (!(*stock_fd)->buff)
		return (0);
	(*stock_fd)->begin = (char *)ft_calloc(1, sizeof(char));
	if (!(*stock_fd)->begin)
		return (0);
	(*stock_fd)->line_start = (*stock_fd)->begin;
	return (1);
}

static char	*no_line(t_stock **stock_fd)
{
	free((*stock_fd)->buff);
	free((*stock_fd)->begin);
	free((*stock_fd));
	(*stock_fd) = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_stock	*stock[OPEN_MAX];
	int				size;

	if (fd < 0 || fd > OPEN_MAX || read(fd, NULL, 0) == -1)
		return (NULL);
	if (!stock[fd] && !init_stock(&stock[fd]))
		return (NULL);
	stock[fd]->line_end = ft_strchr(stock[fd]->line_start, '\n');
	if (stock[fd]->line_end)
		return (extract_line(&stock[fd]));
	while (19)
	{
		size = read(fd, stock[fd]->buff, BUFF_SIZE);
		if (size <= 0)
			break ;
		if (!(join_buff(&stock[fd], size)))
			return (NULL);
		stock[fd]->line_end = ft_strchr(stock[fd]->line_start, '\n');
		if (stock[fd]->line_end)
			return (extract_line(&stock[fd]));
	}
	stock[fd]->line_end = ft_strchr(stock[fd]->line_start, 0);
	if (size < BUFF_SIZE && *stock[fd]->line_start)
		return (extract_line(&stock[fd]));
	return (no_line(&stock[fd]));
}
