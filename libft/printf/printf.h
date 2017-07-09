/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <hpelat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 17:12:15 by hpelat            #+#    #+#             */
/*   Updated: 2017/07/02 14:25:00 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <fcntl.h>
# include <locale.h>

# define A_BONBON       "\e[38;5;164m"
# define A_BROWN        "\e[38;5;52m"
# define A_ORANGE       "\e[38;5;208m"
# define A_DARKBLUE     "\e[38;5;17m"
# define A_DARKGREEN    "\e[38;5;94m"
# define A_LIGHTYELLOW  "\e[38;5;226m"
# define A_PINK         "\e[38;5;211m"
# define A_DARKBONBON   "\e[38;5;89m"
# define A_CLEARBLUE    "\e[38;5;39m"

# define I				"\033[0m"
# define BOLD			"\033[1m"
# define DIM			"\033[2m"
# define UNDERLINED		"\033[4m"
# define BLINK			"\033[5m"
# define REVERSE		"\033[7m"
# define HIDDEN			"\033[8m"

# define BLACK			"\033[0;30m"
# define RED			"\033[0;31m"
# define GREEN			"\033[0;32m"
# define YELLOW			"\033[0;33m"
# define BLUE			"\033[0;34m"
# define PURPLE			"\033[0;35m"
# define CYAN			"\033[0;36m"
# define WHITE			"\033[0;37m"

# define B_BLACK		"\033[1;30m"
# define B_RED			"\033[1;31m"
# define B_GREEN		"\033[1;32m"
# define B_YELLOW		"\033[1;33m"
# define B_BLUE			"\033[1;34m"
# define B_PURPLE		"\033[1;35m"
# define B_CYAN			"\033[1;36m"
# define B_WHITE		"\033[1;37m"

# define H_BLACK		"\033[1;90m"
# define H_RED			"\033[1;91m"
# define H_GREEN		"\033[1;92m"
# define H_YELLOW		"\033[1;93m"
# define H_BLUE			"\033[1;94m"
# define H_PURPLE		"\033[1;95m"
# define H_CYAN			"\033[1;96m"
# define H_WHITE		"\033[1;97m"

# define BK_BLACK		"\033[40m"
# define BK_RED			"\033[41m"
# define BK_GREEN		"\033[42m"
# define BK_YELLOW		"\033[43m"
# define BK_BLUE		"\033[44m"
# define BK_PURPLE		"\033[45m"
# define BK_CYAN		"\033[46m"
# define BK_WHITE		"\033[47m"

# define BKI_BLACK		"\033[100m"
# define BKI_RED		"\033[101m"
# define BKI_GREEN		"\033[102m"
# define BKI_YELLOW		"\033[103m"
# define BKI_BLUE		"\033[104m"
# define BKI_PURPLE		"\033[105m"
# define BKI_CYAN		"\033[106m"
# define BKI_WHITE		"\033[107m"

typedef struct	s_b
{
	char		buff[1024];
	int			pos;
	int			len;
	int			fd;
	int			error;
}				t_b;

typedef struct	s_flags
{
	long int	pl;
	long int	pr;
	long int	isp;
	long int	mfw;
	long int	zer;
	long int	min;
	long int	diez;
	long int	nbr;
}				t_flags;

typedef struct	s_ptf
{
	void		(*ptr)(va_list ap, t_b *b, char *format);
	char		c;
}				t_ptf;

int				ft_printf(const char *restrict format, ...);
int				fd_printf(int fd, const char *restrict format, ...);
int				ft_direct(va_list ap, t_b *b, char *format);
int				ft_whichconv(va_list ap, t_b *b, char *format, t_ptf *ptf);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				ft_mfw(char *str);

void			ft_conv_s(va_list ap, t_b *b, char *format);
void			ft_conv_ls(va_list ap, t_b *b, char *format);
void			ft_conv_p(va_list ap, t_b *b, char *format);
void			ft_conv_d(va_list ap, t_b *b, char *format);
void			ft_conv_o(va_list ap, t_b *b, char *format);
void			ft_conv_u(va_list ap, t_b *b, char *format);
void			ft_conv_x(va_list ap, t_b *b, char *format);
void			ft_conv_c(va_list ap, t_b *b, char *format);
void			ft_conv_lc(va_list ap, t_b *b, char *format);
void			ft_conv_b(va_list ap, t_b *b, char *format);
void			ft_conv_n(va_list ap, t_b *b, char *format);
void			ft_conv_r(va_list ap, t_b *b, char *format);
void			ft_color(va_list ap, t_b *b, char *format);
void			ft_order_p(t_b *b, t_flags flags, char *str, char *rec);
void			ft_order_d(t_b *b, t_flags flags, char *str, char *rec);
void			ft_order_o(t_b *b, t_flags flags, char *str, char *rec);
void			ft_order_u(t_b *b, t_flags flags, char *str, char *rec);
void			ft_order_x(t_b *b, t_flags flags, char *str, char *rec);
void			ft_order_b(t_b *b, t_flags flags, char *str, char *rec);
void			ft_reset(t_b *b);
void			ft_plusminus(t_b *b, t_flags flags);
void			ft_precision(char *str, t_flags *flags);
void			ft_do_mfw(t_b *b, t_flags flags);
void			ft_do_prec(t_b *b, t_flags *flags, char *str);
void			ft_tmp_ls(t_b *b, char *str, wchar_t *rec);
void			ft_space(t_b *b, char *str, t_flags flags, long int nbr);
void			ft_maj(char **rec);

char			ft_findc(char *format, int *i);

char			*ft_strchr(const char *s, int c);
char			*ft_get_wchar(t_b *b, unsigned int lettre);
char			*ft_strcat(char *src, const char *dest);
char			*ft_strcpy(char *dest, const char *src);

void			ft_buffill(t_b *b, char *tmp);
void			ft_itoa_long_nm(char **rec, long int n);
void			ft_itoa_ulong_nm(char **rec, unsigned long int n);
void			ft_itoa_base_long_nm(char **rec, long int n, int base);
void			ft_itoa_base_ulong_nm(char **rec, unsigned long int n,
				int base);

size_t			ft_strlen(const char *str);
size_t			ft_wstrlen(wchar_t *wstr);

static t_ptf	g_tab[] =
{
	{&ft_conv_s, 's'},
	{&ft_conv_ls, 'S'},
	{&ft_conv_p, 'p'},
	{&ft_conv_d, 'd'},
	{&ft_conv_d, 'D'},
	{&ft_conv_d, 'i'},
	{&ft_conv_o, 'o'},
	{&ft_conv_o, 'O'},
	{&ft_conv_u, 'u'},
	{&ft_conv_u, 'U'},
	{&ft_conv_x, 'x'},
	{&ft_conv_x, 'X'},
	{&ft_conv_c, 'c'},
	{&ft_conv_lc, 'C'},
	{&ft_conv_b, 'b'},
	{&ft_conv_n, 'n'},
	{&ft_conv_r, '%'},
	{&ft_color, '@'},
	{NULL, '\0'}
};
#endif
