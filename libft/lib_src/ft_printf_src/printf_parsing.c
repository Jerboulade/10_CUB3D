/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcarere <jcarere@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 17:14:53 by jcarere           #+#    #+#             */
/*   Updated: 2022/01/15 17:14:59 by jcarere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_arg(t_arg *arg)
{
	arg->spec = 0;
	arg->plus_flag = 0;
	arg->just_left = 0;
	arg->space_flag = 0;
	arg->hash = 0;
	arg->zero_flag = 0;
	arg->width = 0;
	arg->precision = -1;
	arg->h_length = 0;
	arg->l_length = 0;
	arg->long_double_length = 0;
	arg->return_val = 0;
}

int	parse_tag(va_list ap, char **format, t_arg *arg)
{
	while (**format)
	{
		if ((**format == '+') || (**format == '-') || (**format == ' ') || \
			(**format == '0') || (**format == '#'))
			get_flags(format, arg);
		else if (ft_isdigit(**format) || (**format == '*'))
			get_width(ap, format, arg);
		else if (**format == '.')
			get_precision(ap, format, arg);
		else if ((**format == 'h') || (**format == 'l') || (**format == 'L'))
			get_length(format, arg);
		else if ((**format == 'd') || (**format == 'i') || (**format == 'e') || \
			(**format == 'u') || (**format == 'x') || (**format == 'X') || \
			(**format == 'c') || (**format == 's') || (**format == 'p') || \
			(**format == 'f') || (**format == '%') || (**format == 'n'))
			return (get_specifier(ap, format, arg));
		else
			break ;
	}
	if (!arg->just_left)
		ft_putpad(arg->width - (arg->width != 0), 0, arg);
	else
		arg->return_val += arg->width - (arg->width != 0);
	return (arg->return_val);
}

char	*ft_findpc(const char *s)
{
	while (*s)
	{
		if (*s == '%')
			return ((char *)s);
		s++;
	}
	return ((char *)s);
}

int	parse_format(char **format, va_list ap, int fd)
{
	char	*tmp;
	int		ret;
	t_arg	arg;

	ret = 0;
	arg.fd = fd;
	while (**format)
	{
		if (**format == '%')
		{
			init_arg(&arg);
			(*format)++;
			arg.return_val = ret;
			ret = parse_tag(ap, format, &arg);
		}
		if (!**format)
			break ;
		tmp = ft_findpc(*format);
		ret += write(arg.fd, *format, tmp - *format);
		*format = tmp;
	}
	return (ret);
}
