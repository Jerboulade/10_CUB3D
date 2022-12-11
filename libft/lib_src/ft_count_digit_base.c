/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_digit_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:15:17 by jcarere           #+#    #+#             */
/*   Updated: 2022/01/10 16:22:19 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_digit_base(uintmax_t n, unsigned int base)
{
	int	count;

	count = 1;
	while (n >= base)
	{
		n /= base;
		count++;
	}
	return (count);
}
