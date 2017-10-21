/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 11:44:30 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/21 11:57:32 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*build_float(t_arg *arg)
{
	char		*num;
	long double	f;
	float		base;
	int			precision;

	f = get_float(arg);
	base = (ft_tolower(arg->conv) == 'a') ? 16.0 : 10.0;
	if (F(F_PRECISE))
		precision = arg->precision;
	else
		precision = (arg->precision) ? arg->precision : 6;
	if (f < 0)
	{
		arg->prefix[0] = '-';
		f *= -1.0;
	}
	if (f != f)
		num = (ft_isupper(arg->conv)) ? "NAN" : "nan";
	else if (f == 1.0 / 0.0 || f == -1.0 / 0.0)
		num = (ft_isupper(arg->conv)) ? "INF" : "inf";
	else
		num = pf_ftoa(f, precision, base);
	return (num);
}

int		print_float(t_arg *arg)
{
	char	*num;
	int		out_len;

	num = build_float(arg);
	out_len = 0;
	if (arg->prefix[0])
		out_len += write(1, arg->prefix, 1);
	if (!F(F_SPECIAL))
		out_len += write(1, (ft_isupper(arg->conv)) ? "0X" : "0x", 2);
	out_len += write(1, num, ft_strlen(num));
	if (ft_isdigit(*num))
		free(num);
	return (out_len);
}
