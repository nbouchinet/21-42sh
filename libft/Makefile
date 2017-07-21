# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/17 18:14:45 by khabbar           #+#    #+#              #
#    Updated: 2017/07/20 17:58:48 by khabbar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

MOD = get_next_line libft printf

SRC = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	  ft_isdigit.c ft_isprint.c ft_itoa.c ft_memalloc.c ft_memccpy.c \
	  ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c \
	  ft_memset.c ft_putchar.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr.c \
	  ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c ft_strcat.c ft_strchr.c \
	  ft_strclr.c ft_strcmp.c ft_strcpy.c ft_strdel.c ft_strdup.c \
	  ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
	  ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
	  ft_strncpy.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
      ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_tolower.c \
	  ft_toupper.c ft_putendl.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c \
	  ft_lstnew.c ft_lstiter.c ft_lstmap.c ft_wstrlen.c \
	  ft_isupper.c get_next_line.c ft_iterative_factorial.c \
	  ft_iterative_power.c convert_to_d.c ft_putnbrl.c ft_display_tab.c \
	  ft_itoa_base.c display_int_tab.c ft_strjoinf.c \
	  ft_printf.c ft_direct.c ft_whichconv.c ft_findc.c ft_conv_s.c \
	  ft_conv_ls.c ft_conv_p.c ft_conv_d.c ft_conv_o.c ft_conv_u.c \
	  ft_conv_x.c ft_conv_c.c ft_conv_lc.c ft_conv_b.c ft_conv_n.c \
	  ft_conv_r.c  ft_color.c ft_reset.c ft_buffill.c ft_wstrlen.c \
	  ft_itoa_long_nm.c ft_itoa_ulong_nm.c ft_itoa_base_long_nm.c \
	  ft_itoa_base_ulong_nm.c ft_mfw.c ft_do_mfw.c ft_precision.c \
	  ft_do_prec.c ft_order_p.c ft_order_d.c ft_order_o.c ft_order_u.c \
	  ft_order_x.c ft_order_b.c ft_plusminus.c ft_get_wchar.c \
	  ft_tmp_ls.c ft_space.c ft_maj.c ft_intlen.c fd_printf.c ft_tablen.c \
	  ft_free.c ft_strat.c ft_strtrimf.c ft_strenv.c ft_strdupf.c \
	  ft_streplace.c ft_errormsg.c ft_strndup.c	ft_strdups.c ft_strdigit.c\

OBJ = ${SRC:.c=.o}

VPATH = libf:get_next_line:printf

all: $(NAME) inc/libftprintf.h

%.o : %.c
	@$(CC) $(CFLAGS) -c -o $@ $^

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@/bin/rm -rf $(OBJ)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all
