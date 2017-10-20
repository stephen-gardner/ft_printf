/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgardner <stephenbgardner@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 12:10:24 by sgardner          #+#    #+#             */
/*   Updated: 2017/10/19 20:52:32 by sgardner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# define F(f) (arg->flags & f)
# define BASE_KEY "0123456789abcdef"

typedef struct	s_arg
{
	va_list	*ap;
	char	conv;
	char	prefix[3];
	int		flags;
	int		width;
	int		precision;
}				t_arg;

typedef struct	s_conv
{
	char	specifier;
	int		(*handle)(t_arg *);
}				t_conv;

enum	e_flags
{
	F_H = 1,
	F_HH = 1 << 1,
	F_L = 1 << 2,
	F_LD = 1 << 3,
	F_LL = 1 << 4,
	F_J = 1 << 5,
	F_Z = 1 << 6,
	F_PRECISE = 1 << 7,
	F_MINUS = 1 << 8,
	F_PLUS = 1 << 9,
	F_SPACE = 1 << 10,
	F_ZERO = 1 << 11,
	F_HASH = 1 << 12
};

/*
** dispatcher.c
*/

int				dispatch(t_arg *arg);

/*
** ft_printf.c
*/

int				ft_printf(const char *format, ...);

/*
** int_handlers.c
*/

int				print_d(t_arg *arg);
int				print_o(t_arg *arg);
int				print_p(t_arg *arg);
int				print_u(t_arg *arg);
int				print_x(t_arg *arg);

/*
** int_handlers_deprecated.c
*/

int				print_ld_deprecated(t_arg *arg);
int				print_lo_deprecated(t_arg *arg);
int				print_lu_deprecated(t_arg *arg);

/*
** parser.c
*/

int				handle_arg(const char **fmt, va_list *ap);

/*
** print_char.c
*/

int				print_char(t_arg *arg);
int				print_percent(t_arg *arg);
int				print_str(t_arg *arg);

/*
** print_float.c
*/

char			*get_float(t_arg *arg);
int				print_float(t_arg *arg);

/*
** print_int.c
*/

int				print_int(t_arg *arg, int base, t_bool is_signed);

/*
** util.c
*/

intmax_t		get_int(t_arg *arg);
uintmax_t		get_uint(t_arg *arg);
char			*pf_itoa(t_arg *arg, intmax_t n, int base);
char			*pf_uitoa(uintmax_t un, int base);
int				write_pad(int size, char c);

extern const t_conv	g_disp[];
extern const int	g_disp_count;
#endif
