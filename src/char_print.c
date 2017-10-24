/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 21:55:13 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/23 17:08:41 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print(char *s, t_arg *arg, int len)
{
	int	pad;
	int	out_len;

	out_len = 0;
	pad = arg->width - len;
	if (pad > 0 && !F(F_MINUS))
		out_len += write_pad(pad, ' ');
	out_len += write(1, s, len);
	if (pad > 0 && F(F_MINUS))
		out_len += write_pad(pad, ' ');
	return (out_len);
}

int			print_str(t_arg *arg)
{
	char	*out;
	wchar_t	*ws;
	int		len;
	int		out_len;

	if (F(F_L) || arg->conv == 'S')
	{
		if (!(ws = va_arg(*arg->ap, wchar_t *)))
			ws = L"(null)";
		len = ft_wcnlen(ws);
		if (F(F_PRECISE) && len > arg->precision)
			len = arg->precision;
		if (!(out = (char *)ft_memalloc(len + 1)))
			return (-1);
		ft_wctouc((t_byte *)out, ws, len);
		out_len = print(out, arg, len);
		free(out);
		return (out_len);
	}
	if (!(out = va_arg(*arg->ap, char *)))
		out = "(null)";
	len = ft_strlen(out);
	if (F(F_PRECISE) && len > arg->precision)
		len = arg->precision;
	return ((out_len = print(out, arg, len)));
}

int			print_char(t_arg *arg)
{
	char	c;
	int		out_len;

	c = (char)va_arg(*arg->ap, int);
	out_len = print(&c, arg, 1);
	return (out_len);
}

int			print_percent(t_arg *arg)
{
	char	*str;

	str = "%";
	if (!arg->precision)
		arg->precision = 1;
	return (print(str, arg, 1));
}
