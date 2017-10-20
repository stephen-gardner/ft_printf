/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 11:44:30 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/19 22:26:54 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "ft_printf.h"

static void	round_fstring(char *num, int base)
{
	char	*end;

	end = num;
	if (*num >= BASE_KEY[base / 2])
	{
		num--;
		while (*num == BASE_KEY[base - 1] || *num == '.')
		{
			if (*num != '.')
				*num = '0';
			num--;
		}
		*num = BASE_KEY[(*num - '0') + 1];
	}
	*end = '\0';
}

static void	load_mantissa(char *num, long double f, int precision, float base)
{
	if (precision == -1)
	{
		*num = BASE_KEY[(int)(f * base)];
		round_fstring(num, (int)base);
	}
	else
	{
		*num++ = '.';
		precision++;
		while (precision--)
		{
			f *= base;
			*num++ = BASE_KEY[(int)f];
			f -= (int)f;
		}
		*num = '\0';
		round_fstring(num - 1, (int)base);
	}
}

static char	*pf_ftoa(long double f, int precision, float base)
{
	char		*num;
	double		power;
	int			len;
	int			digit;
	int			i;

	power = 1.0;
	len = 2;
	while (power < f / base && len++)
		power *= base;
	num = (char *)malloc(len + (precision > 0) + precision + 1);
	i = 0;
	if (f < 1.0)
		num[i++] = '0';
	while (f >= 1.0)
	{
		digit = (int)(f / power);
		num[i++] = BASE_KEY[digit];
		f -= digit * power;
		power /= base;
	}
	if (precision == 0)
		precision = -1;
	load_mantissa(&num[i], f, precision, base);
	return (num);
}

char	*get_float(t_arg *arg)
{
	char		*num;
	long double	f;
	int			precision;
	float		base;

	f = (F(F_LD)) ? va_arg(*arg->ap, long double) : va_arg(*arg->ap, double);
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
		num = "nan";
	else if (f == INFINITY)
		num = "inf";
	else
		num = pf_ftoa(f, precision, base);
	return (num);
}

int		print_float(t_arg *arg)
{
	char	*num;

	num = get_float(arg);
	if (arg->prefix[0])
		write(1, arg->prefix, 1);
	printf("%s\n", num);
	if (ft_isdigit(*num))
		free(num);
	return (1);
}