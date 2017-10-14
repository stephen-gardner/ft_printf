/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 18:23:34 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/13 23:20:52 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*pf_itoa(t_arg *arg, intmax_t n, int base)
{
	uintmax_t	un;

	if (n < 0)
	{
		arg->prefix[0] = '-';
		un = (uintmax_t)(n * -1);
	}
	else
		un = (uintmax_t)n;
	return (pf_uitoa(un, base));
}

char	*pf_uitoa(uintmax_t un, int base)
{
	char	num[23];
	int		digit;

	num[22] = '\0';
	digit = 21;
	if (un == 0)
		num[digit--] = '0';
	while (un != 0)
	{
		num[digit--] = "0123456789abcdef"[un % base];
		un /= base;
	}
	return (ft_strdup(&num[++digit]));
}

int		write_pad(int size, char c)
{
	int	i;

	i = 0;
	while (i < size)
	{
		write(1, &c, 1);
		i++;
	}
	return (size);
}
