/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 20:27:22 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/21 16:58:39 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

const t_conv	g_disp[] = {
	{ '%', &print_percent },
	{ 'C', &print_char },
	{ 'c', &print_char },
	{ 'D', &print_ld_deprecated },
	{ 'd', &print_d },
	{ 'F', &print_float },
	{ 'f', &print_float },
	{ 'i', &print_d },
	{ 'O', &print_lo_deprecated },
	{ 'o', &print_o },
	{ 'p', &print_p },
	{ 'S', &print_str },
	{ 's', &print_str },
	{ 'U', &print_lu_deprecated },
	{ 'u', &print_u },
	{ 'X', &print_x },
	{ 'x', &print_x },
};
const int		g_disp_count = sizeof(g_disp) / sizeof(t_conv);

int				dispatch(t_arg *arg)
{
	t_conv	disp;
	int		i;

	i = 0;
	while (i < g_disp_count)
	{
		disp = g_disp[i++];
		if (arg->conv == disp.specifier)
			return (disp.handle(arg));
	}
	return (0);
}

int				ft_printf(const char *format, ...)
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

void			set_prefix(t_arg *arg, int base, char *num)
{
	if (*arg->prefix)
		return ;
	if (F(F_HASH) && (arg->conv == 'p' || *num != '0'))
	{
		if (base == 16 || base == 8)
			arg->prefix[0] = '0';
		if (base == 16)
			arg->prefix[1] = arg->conv;
	}
	if (base != 10)
		return ;
	if (F(F_PLUS))
		*arg->prefix = '+';
	else if (F(F_SPACE))
		*arg->prefix = ' ';
}

int				write_pad(int size, char c)
{
	int	i;

	i = 0;
	while (i++ < size)
		write(1, &c, 1);
	return (size);
}
