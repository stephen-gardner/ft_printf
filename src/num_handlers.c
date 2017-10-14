/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 18:31:17 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/13 23:15:54 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			print_d(t_arg *arg)
{
	va_list	copy;

	va_copy(copy, *arg->ap);
	if (!va_arg(copy, int) && F(F_PRECISE) && !arg->precision)
		return (write_pad(arg->width, ' '));
	return (print_num(arg, 10, TRUE));
}

int			print_o(t_arg *arg)
{
	if (F(F_PRECISE) && !arg->precision && !F(F_HASH))
		return (write_pad(arg->width, ' '));
	return (print_num(arg, 8, FALSE));
}

int			print_p(t_arg *arg)
{
	arg->flags |= F_HASH;
	return (print_num(arg, 16, FALSE));
}

int			print_u(t_arg *arg)
{
	return (print_num(arg, 10, FALSE));
}

int			print_x(t_arg *arg)
{
	if (F(F_PRECISE) && !arg->precision)
		return (write_pad(arg->width, ' '));
	return (print_num(arg, 16, FALSE));
}
