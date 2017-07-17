/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 17:52:39 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/09 14:35:06 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

typedef struct		s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}					t_env;

#include "../libft/inc/libftprintf.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <term.h>
#include <curses.h>
#include <signal.h>
#include <sys/ioctl.h>
#include "command_line.h"
#include "lexer_parser.h"
#include "AST.h"
#include "exec.h"

void		ft_putast(t_ast *root);

#endif
