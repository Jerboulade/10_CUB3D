/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unitoa_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:14:15 by jcarere           #+#    #+#             */
/*   Updated: 2022/01/10 17:02:05 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_unitoa_base(uintmax_t nb, char *base_tab, size_t base)
{
	char	*tab;
	int		i;

	tab = NULL;
	i = ft_count_digit_base(nb, base);
	tab = (char *)ft_calloc(i + 1, sizeof(char));
	if (!tab)
		return (NULL);
	tab[i] = 0;
	i--;
	if (!nb)
		tab[i] = '0';
	while (nb)
	{
		tab[i--] = base_tab[nb % base];
		nb /= base;
	}
	return (tab);
}
