/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:01:45 by khabbar           #+#    #+#             */
/*   Updated: 2017/08/23 14:07:57 by zadrien          ###   ########.fr       */
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
	t_tok	*tok;

	init_token(&cmd);
	new_parser(&cmd, *line);
	lexer_check(&cmd);
	expanse(&cmd, env);
	if (!cmd)
		return ;
		tok = cmd;
	while (tok)
	{
		ft_printf("%@%s%@\n", BLUE, tok->str, I);
		tok = tok->n;
	}
	init_ast(&ast, NULL, 0);
	primary_sequence(&ast, &cmd);
	ft_putast(ast);
	job_ast(&ast, env);
	// exec_ast(&ast, env);
	destroy_ast(&ast);
	destroy_tok(&cmd);
}

static void	loop(t_win *win)
{
	char	*cmd;
	char	buf[6];

	while (g_loop)
	{
		job_control(NULL, NULL, UPT); // AST NULL
		job_control(NULL, NULL, CHK);
		cmd = NULL;
		get_cmdl(&cmd, &win, NULL, buf);
		if (win->ctrld)
			break ;
		if (cmd && !(cmd[0] == '\\' && cmd[1] == 0))
		{
			ft_printf("\n%@%s%@\n", RED, cmd, I);
			mode_off(&win);
			exec_part(&cmd, &win->lstenv);
			mode_on(&win);
		}
		cmd ? free(cmd) : 0;
		t_local *loc = *local_sgt(0);
		while (loc)
		{
			ft_printf("PRINT: %s=%s\n", loc->var, loc->val);
			loc = loc->n;
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
	win->his->add = 1;
	win->his->prev = NULL;
  	win->his->next = NULL;
	win->his->len = 0;
	g_loop = 256;
	hist_read(&win->his, 0, -50);
	loop(win);
	return (g_loop);
}
