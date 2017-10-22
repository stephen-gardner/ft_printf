/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/22 23:53:24 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/23 16:09:10 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_wctoutf(t_byte *dst, wchar_t *src, int size)
{
	if (!size)
		*dst = *src;
	else
	{
		if (size < 2)
			*dst++ = 0xC0 | (*src >> 6);
		else if (size < 3)
			*dst++ = 0xE0 | (*src >> 12);
		else
			*dst++ = 0xF0 | (*src >> 18);
		while (size--)
			*dst++ = 0x80 | ((*src >> (size * 6)) & 0x3F);
	}
}

int			ft_utflen(wchar_t *ws, int maxlen)
{
	int	len;
	int	size;

	len = 0;
	while (*ws)
	{
		if (*ws <= 0x7F)
			size = 1;
		else if (*ws <= 0x7FF)
			size = 2;
		else if (*ws <= 0xFFFF)
			size = 3;
		else if (*ws <= 0x10FFFF)
			size = 4;
		else
			break ;
		if (len + size > maxlen)
			break ;
		len += size;
		ws++;
	}
	return (len);
}

/*
** For C/POSIX locale
*/

int			ft_wcnlen(wchar_t *ws)
{
	int	len;

	len = 0;
	while (ws[len] && ws[len] < 0x100)
		len++;
	return (len);
}

/*
** For C/POSIX locale
*/

void		ft_wctouc(t_byte *dst, wchar_t *src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		dst[i] = (t_byte)src[i];
		i++;
	}
}

void		ft_wctoutf_str(t_byte *dst, wchar_t *src, int maxlen)
{
	int	len;
	int	size;

	len = 0;
	while (*src)
	{
		if (*src <= 0x7F)
			size = 1;
		if (*src <= 0x7FF)
			size = 2;
		else if (*src <= 0xFFFF)
			size = 3;
		else if (*src <= 0x10FFFF)
			size = 4;
		else
			break ;
		if (len + size > maxlen)
			break ;
		dst += size;
		len += size;
		ft_wctoutf(dst, src++, size - 1);
	}
}
