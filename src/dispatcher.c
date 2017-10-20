/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 15:50:40 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/16 12:49:48 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const t_conv	g_disp[] = {
	{ '%', &print_percent },
	{ 'C', &print_char },
	{ 'c', &print_char },
	{ 'D', &print_ld_deprecated },
	{ 'd', &print_d },
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

int	dispatch(t_arg *arg)
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
