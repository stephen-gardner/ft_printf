/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 21:55:13 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/14 14:18:14 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	fit_wchar(t_byte *str, int len)
{
	int	i;

	i = (len - 5 > 0) ? len - 5 : 0;
	while (str[i])
	{
		if (str[i] <= 0xBF && i < len)
			i++;
		else if (str[i] >= 0xF0 && str[i] <= 0xFF && i + 3 < len)
			i += 4;
		else if (str[i] >= 0xE0 && str[i] <= 0xEF && i + 2 < len)
			i += 3;
		else if (str[i] >= 0xC2 && str[i] <= 0xDF && i + 1 < len)
			i += 2;
		else
			return (i);
	}
	return (i + 1);
}

static int	print(char *str, t_arg *arg)
{
	int		len;
	int		pad;
	int		out_len;

	len = (arg->flags & F_PRECISE)
		? ft_strnlen(str, arg->precision) : ft_strlen(str);
	if (arg->flags & F_L || arg->conv == 'S')
		len = fit_wchar((t_byte *)str, len);
	pad = arg->width - len;
	out_len = 0;
	if (pad > 0 && !F(F_MINUS))
		out_len += write_pad(pad, ' ');
	out_len += write(1, str, len);
	if (pad > 0 && F(F_MINUS))
		out_len += write_pad(pad, ' ');
	return (out_len);
}

int			print_char(t_arg *arg)
{
	char	c;
	int		out_len;

	c = (char)va_arg(*arg->ap, int);
	out_len = 0;
	if (arg->width > 1 && !F(F_MINUS))
		out_len += write_pad(arg->width - 1, ' ');
	out_len += write(1, &c, 1);
	if (arg->width > 1 && F(F_MINUS))
		out_len += write_pad(arg->width - 1, ' ');
	return (out_len);
}

int			print_percent(t_arg *arg)
{
	char	*str;

	str = "%";
	if (!arg->precision)
		arg->precision = 1;
	return (print(str, arg));
}

int			print_str(t_arg *arg)
{
	char	*str;

	if (!(str = va_arg(*arg->ap, char *)))
		str = "(null)";
	return (print(str, arg));
}
