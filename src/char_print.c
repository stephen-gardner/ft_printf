/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 21:55:13 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/23 16:09:07 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		print_str(char *str, t_arg *arg)
{
	int             len;
	int             pad;
	int             out_len;

	len = (F(F_PRECISE)) ? ft_strnlen(str, arg->precision) : ft_strlen(str);
	pad = arg->width - len;
	out_len = 0;
	if (pad > 0 && !F(F_MINUS))
		out_len += write_pad(pad, ' ');
	out_len += write(1, str, len);
	if (pad > 0 && F(F_MINUS))
		out_len += write_pad(pad, ' ');
	return (out_len);
}

static int		print_wstr(wchar_t *ws, t_arg *arg)
{
	t_byte	*out;
	int		len;
	int		pad;
	int		out_len;

	len = ft_wcnlen(ws);
	if (F(F_PRECISE) && len > arg->precision)
		len = arg->precision;
	out = (t_byte *)ft_memalloc(len + 1);
	ft_wctouc(out, ws, len);
	pad = arg->width - len;
	out_len = 0;
	if (pad > 0 && !F(F_MINUS))
		out_len += write_pad(pad, ' ');
	out_len += write(1, out, len);
	if (pad > 0 && F(F_MINUS))
		out_len += write_pad(pad, ' ');
	free(out);
	return (out_len);
}

int				print_char(t_arg *arg)
{
	t_byte	c;
	int		out_len;

	if (F(F_L))
		return (print_wchar(arg));
	c = (char)va_arg(*arg->ap, int);
	out_len = 0;
	if (arg->width > 1 && !F(F_MINUS))
		out_len += write_pad(arg->width - 1, ' ');
	out_len += write(1, &c, 1);
	if (arg->width > 1 && F(F_MINUS))
		out_len += write_pad(arg->width - 1, ' ');
	return (out_len);
}

int				print_wchar(t_arg *arg)
{
	t_byte	out;
	int		out_len;
	
	out = (t_byte)va_arg(*arg->ap, wint_t);
	out_len = 0;
	if (arg->width > 1 && !F(F_MINUS))
		out_len += write_pad(arg->width - 1, ' ');
	out_len += write(1, &out, 1);
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
	return (print_str(str, arg));
}

int			print_s(t_arg *arg)
{
	char	*str;
	wchar_t	*wstr;

	if (F(F_L) || arg->conv == 'S')
	{
		if (!(wstr = va_arg(*arg->ap, wchar_t *)))
			wstr = L"(null)";
		return (print_wstr(wstr, arg));
	}
	else
	{
		if (!(str = va_arg(*arg->ap, char *)))
			str = "(null)";
		return (print_str(str, arg));
	}
}
