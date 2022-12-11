/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_int_manip.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:52:39 by jcarere           #+#    #+#             */
/*   Updated: 2022/01/10 17:27:11 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	shift_tab_right(t_fl *flo)
{
	int	end;
	int	i;

	end = flo->nb_buff - 1;
	i = end;
	while (!flo->big_int[i])
		i--;
	if (i == end)
		return ;
	while (i >= 0)
	{
		flo->big_int[end--] = flo->big_int[i];
		flo->big_int[i--] = 0;
	}
	i = flo->nb_buff;
	while (--i)
	{
		if (flo->big_int[i] >= 1000000000000000000)
		{
			flo->big_int[i - 1]++;
			flo->big_int[i] -= 1000000000000000000;
		}
	}
}

void	shift_tab_left(t_fl *flo)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (!flo->big_int[i])
		i++;
	if (!i)
		return ;
	while (i < flo->nb_buff)
	{
		flo->big_int[start++] = flo->big_int[i];
		flo->big_int[i++] = 0;
	}
}

void	div_big_int(uintmax_t *mantissa_value, int nb_buff, int time)
{
	int	i;
	int	is_odd;
	int	previous_is_odd;

	while (time)
	{
		i = 0;
		is_odd = 0;
		previous_is_odd = 0;
		while (i != nb_buff)
		{
			is_odd = (mantissa_value[i] % 2);
			if (mantissa_value[i])
				mantissa_value[i] >>= 1;
			if (previous_is_odd)
				mantissa_value[i] += 500000000000000000;
			previous_is_odd = is_odd;
			i++;
		}
		time--;
	}
}

void	mult_big_int(t_fl *flo, int time, char is_full, char previous_is_full)
{
	int	i;

	while (time)
	{
		i = flo->nb_buff;
		is_full = 0;
		previous_is_full = 0;
		while (--i >= 0)
		{
			if (flo->big_int[i])
				flo->big_int[i] <<= 1;
			flo->big_int[i] += previous_is_full;
			if (flo->big_int[i] >= 1000000000000000000)
			{
				is_full = 1;
				flo->big_int[i] -= 1000000000000000000;
			}
			else
				is_full = 0;
			previous_is_full = is_full;
		}
		if (!flo->big_int[flo->nb_buff - 1])
			shift_tab_right(flo);
		time--;
	}
}

void	sum_mantissa(t_fl *flo, char *mantissa)
{
	uintmax_t	unit[6];
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (mantissa[j])
	{
		if (mantissa[j++] == '1')
		{
			unit[i] = 1000000000000000000;
			while (++i < 6)
				unit[i] = 0;
			div_big_int(unit, 6, j);
			while (--i)
			{
				if (flo->big_int[i] >= 1000000000000000000)
				{
					flo->big_int[i - 1] += 1;
					flo->big_int[i] -= 1000000000000000000;
				}
				flo->big_int[i - 1] += unit[i - 1];
			}
		}
	}
}
