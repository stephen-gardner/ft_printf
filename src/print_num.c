/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 14:28:28 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/13 23:23:01 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	fill_precision(t_arg *arg, char **num)
{
	char	*filled;
	int		len;

	if (!F(F_PRECISE))
		return ;
	if ((len = ft_strlen(*num)) >= arg->precision)
		return ;
	filled = (char *)malloc(arg->precision);
	ft_memset((void *)filled, '0', arg->precision - len);
	ft_memcpy((void *)(filled + (arg->precision - len)), (void *)*num, len);
	filled[arg->precision] = '\0';
	free(*num);
	*num = filled;
}

static void	set_prefix(t_arg *arg, int base, char *num)
{
	if (arg->prefix[0])
		return ;
	if (F(F_HASH))
	{
		if (*num != '0')
		{
			if (base == 16 || base == 8)
				arg->prefix[0] = '0';
			if (base == 16)
				arg->prefix[1] = (arg->conv == 'X') ? 'X' : 'x';
		}
	}
	if (arg->conv != 'd' && arg->conv != 'i' && arg->conv != 'D')
		return ;
	if (F(F_PLUS))
		arg->prefix[0] = '+';
	else if (F(F_SPACE))
		arg->prefix[0] = ' ';
}

static char	*build_num(t_arg *arg, int base, t_bool is_signed)
{
	char	*num;

	if (F(F_H))
		num = (is_signed) ? pf_itoa(arg, (short)va_arg(*arg->ap, int), base)
			: pf_uitoa((unsigned short)va_arg(*arg->ap, unsigned int), base);
	else if (F(F_HH))
		num = (is_signed) ? pf_itoa(arg, (char)va_arg(*arg->ap, int), base)
			: pf_uitoa((unsigned char)va_arg(*arg->ap, unsigned int), base);
	else if (F(F_L))
		num = (is_signed) ? pf_itoa(arg, va_arg(*arg->ap, long), base)
			: pf_uitoa(va_arg(*arg->ap, unsigned long), base);
	else if (F(F_LL))
		num = (is_signed) ? pf_itoa(arg, va_arg(*arg->ap, long long), base)
			: pf_uitoa(va_arg(*arg->ap, unsigned long long), base);
	else if (F(F_J))
		num = (is_signed) ? pf_itoa(arg, va_arg(*arg->ap, intmax_t), base)
			: pf_uitoa(va_arg(*arg->ap, uintmax_t), base);
	else if (F(F_Z) || arg->conv == 'p')
		num = (is_signed) ? pf_itoa(arg, va_arg(*arg->ap, intmax_t), base)
			: pf_uitoa(va_arg(*arg->ap, size_t), base);
	else
		num = (is_signed) ? pf_itoa(arg, va_arg(*arg->ap, int), base)
			: pf_uitoa(va_arg(*arg->ap, unsigned int), base);
	return (num);
}

int			print_num(t_arg *arg, int base, t_bool is_signed)
{
	char	*num;
	int		len;
	int		prefix_len;
	int		pad;
	int		out_len;

	num = build_num(arg, base, is_signed);
	fill_precision(arg, &num);
	set_prefix(arg, base, num);
	len = ft_strlen(num);
	prefix_len = ft_strlen(arg->prefix);
	out_len = 0;
	pad = arg->width - len - prefix_len;
	if (pad > 0 && !F(F_MINUS) && (!F(F_ZERO) || F(F_PRECISE)))
		out_len += write_pad(pad, ' ');
	out_len += write(1, arg->prefix, prefix_len);
	if (pad > 0 && F(F_ZERO) && !F(F_MINUS) && !F(F_PRECISE))
		out_len += write_pad(pad, '0');
	if (arg->conv == 'X')
		ft_strupcase(num);
	out_len += write(1, num, len);
	if (pad > 0 && F(F_MINUS))
		out_len += write_pad(pad, ' ');
	free(num);
	return (out_len);
}
