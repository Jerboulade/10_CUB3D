/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:16:14 by jcarere           #+#    #+#             */
/*   Updated: 2022/01/15 17:19:26 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dprintf(int fd, const char *format, ...)
{
	va_list	ap;
	int		return_val;

	va_start(ap, format);
	return_val = parse_format((char **)&format, ap, fd);
	va_end(ap);
	return (return_val);
}
