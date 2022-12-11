/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 17:51:43 by jcarere           #+#    #+#             */
/*   Updated: 2022/01/10 17:27:33 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	get_flags(char **format, t_arg *arg)
{
	if (**format == '+')
		arg->plus_flag = 1;
	else if (**format == '-')
		arg->just_left = 1;
	else if (**format == ' ')
		arg->space_flag = 1;
	else if (**format == '0')
		arg->zero_flag = 1;
	else if (**format == '#')
		arg->hash = 1;
	(*format)++;
}

void	get_width(va_list ap, char **format, t_arg *arg)
{
	if (**format == '*')
	{
		arg->width = va_arg(ap, int);
		if (arg->width < 0)
		{
			arg->width *= -1;
			arg->just_left = 1;
		}
		(*format)++;
	}
	if (ft_isdigit(**format))
		arg->width = 0;
	while (ft_isdigit(**format))
	{
		arg->width *= 10;
		arg->width += **format - '0';
		(*format)++;
	}
}

void	get_precision(va_list ap, char **format, t_arg *arg)
{
	(*format)++;
	if (**format == '*')
	{
		arg->precision = va_arg(ap, int);
		if (arg->precision < 0)
			arg->precision = -1;
		(*format)++;
	}
	else
	{
		arg->precision = 0;
		while (ft_isdigit(**format))
		{
			arg->precision *= 10;
			arg->precision += **format - '0';
			(*format)++;
		}
	}
}

void	get_length(char **format, t_arg *arg)
{
	char	length;

	length = **format;
	while (**format == length)
	{
		if (**format == 'h')
			arg->h_length++;
		else if (**format == 'l')
			arg->l_length++;
		else if (**format == 'L')
			arg->long_double_length = 1;
		(*format)++;
	}
	while ((**format == 'h') || (**format == 'l') || (**format == 'L'))
		(*format)++;
}

int	get_specifier(va_list ap, char **form, t_arg *arg)
{
	arg->spec = **form;
	if (arg->spec == 'p')
		arg->spec = 'x';
	if (**form == '%')
		handle_pc(arg, form);
	else if (**form == 'n')
		handle_nflag(ap, arg, form);
	else if (**form == 'd' || **form == 'i')
		get_signed_type(ap, form, arg);
	else if (**form == 'p' || **form == 'u' || **form == 'x' || **form == 'X')
		get_unsigned_type(ap, form, arg);
	else if (**form == 'c')
		handle_char(ap, arg, form);
	else if (**form == 's')
		handle_str(ap, arg, form);
	else if (**form == 'f' || **form == 'e')
		handle_fraction(ap, arg, form);
	return (arg->return_val);
}
