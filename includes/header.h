/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 17:52:39 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/20 14:54:56 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H
# include "../libft/inc/libftprintf.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <term.h>
# include <curses.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/param.h>
# include "command_line.h"
# include "lexer_parser.h"
# include "abstract_syntax_tree.h"
# include "job_control.h"
# include "builtins.h"

void				ft_putast(t_ast *root);

#endif
