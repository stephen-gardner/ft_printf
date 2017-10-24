/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 20:27:22 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/23 22:38:21 by sgardner         ###   ########.fr       */
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

static int		print_line(const char *format, va_list *ap, t_bool *error)
{
	const char	*end;
	int			len;
	int			arg_len;

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
			if ((arg_len = handle_arg(&end, ap, len)) < 0)
				*error = TRUE;
			else
				len += arg_len;
		}
		format = end;
	}
	return (len);
}

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
	va_list	ap;
	int		len;
	t_bool	error;

	va_start(ap, format);
	error = FALSE;
	len = print_line(format, &ap, &error);
	va_end(ap);
	return ((error) ? -1 : len);
}

void			set_prefix(t_arg *arg, int base, char *num)
{
	char	conv;

	if (*arg->prefix)
		return ;
	if (F(F_HASH) && (arg->conv == 'p' || *num != '0'))
	{
		if (base == 16 || base == 8)
			arg->prefix[0] = '0';
		if (base == 16)
			arg->prefix[1] = ft_isupper(arg->conv) ? 'X' : 'x';;
	}
	conv = ft_tolower(arg->conv);
	if (conv != 'd' && conv != 'i' && conv != 'f')
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
