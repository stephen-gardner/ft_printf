/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 15:50:40 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/13 21:20:04 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const t_conv	g_disp[] = {
	{ '%', 0, &print_percent },
	{ 'C', 0, &print_char },
	{ 'c', F_L, &print_char },
	{ 'c', 0, &print_char },
	{ 'D', 0, &print_ld_deprecated },
	{ 'd', 0, &print_d },
	{ 'i', 0, &print_d },
	{ 'O', 0, &print_lo_deprecated },
	{ 'o', 0, &print_o },
	{ 'p', 0, &print_p },
	{ 'S', 0, &print_str },
	{ 's', F_L, &print_str },
	{ 's', 0, &print_str },
	{ 'U', 0, &print_lu_deprecated },
	{ 'u', 0, &print_u },
	{ 'X', 0, &print_x },
	{ 'x', 0, &print_x },
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
		if (arg->conv == disp.specifier && (!disp.flags || F(disp.flags)))
			return (disp.handle(arg));
	}
	return (0);
}
