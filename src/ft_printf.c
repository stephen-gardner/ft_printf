/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 20:27:22 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/14 15:48:50 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <locale.h>
#include <wchar.h>
#include <unistd.h>

int	ft_printf(const char *format, ...)
{
	va_list		ap;
	const char	*end;
	int			len;
	int			arg_len;

	va_start(ap, format);
	len = 0;
	while (*format)
	{
		end = format;
		while (*end && *end != '%')
			end++;
		len += write(1, format, end - format);
		if (*end == '%')
		{
			end++;
			if ((arg_len = handle_arg(&end, &ap)) < 0)
				return (-1);
			len += arg_len;
		}
		format = end;
	}
	va_end(ap);
	return (len);
}
