/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:01:45 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/02 17:56:31 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int g_loop;

int			get_win_data(t_win **win)
{
	struct winsize	w;

	if (ioctl(0, TIOCGWINSZ, &w) == -1)
		return (fd_printf(2, "Error while accesing terminal data\n"));
	(*win)->co = w.ws_col;
	(*win)->li = w.ws_row;
	return (0);
}

static void	exec_part(char **line, t_env **env)
{
	t_ast	*ast;
	t_tok	*cmd;
	t_tok	*tmp;

	init_token(&cmd);
	new_parser(&cmd, *line);
	lexer_check(&cmd);
	specified_dir(&cmd);
	tmp = cmd;
	while (tmp)
	{
		ft_putendl(tmp->str);
		tmp = tmp->n;
	}
	if (!cmd)
		return ;
	init_ast(&ast, NULL, 0);
	primary_sequence(&ast, &cmd);
	exec_ast(&ast, env);
	destroy_ast(&ast);
	destroy_tok(&cmd);
}

static void	loop(t_win *win)
{
	char	*cmd;
	int		save;
	char	buf[6];

	while (g_loop)
	{
		save = g_loop;
		cmd = NULL;
		get_cmdl(&cmd, &win, NULL, buf);
		if (win->ctrld)
			break ;
		if (cmd)
		{
			mode_off(&win);
			exec_part(&cmd, &win->lstenv);
			mode_on(&win);
			free(cmd);
		}
	}
	unset_shell(&win);
}

int         main(int ac, char *av[], char *env[])
{
	t_win	*win;

	ac = 0;
	(void)av;
	env = check_env(env);
	if (set_shell(&win)|| get_win_data(&win) || init_env(&(win->lstenv), env))
		return (1);
	if (!(win->his = (t_his *)malloc(sizeof(t_his))))
		exit(fd_printf(2, "malloc error\n"));
	win->his->cmdl = ft_strdup("");
	win->his->prev = NULL;
    win->his->next = NULL;
	win->his->len = 0;
	g_loop = 256;
	loop(win);
	return (g_loop);
}
