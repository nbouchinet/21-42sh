/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:01:45 by khabbar           #+#    #+#             */
/*   Updated: 2017/08/23 10:21:28 by nbouchin         ###   ########.fr       */
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
	//	win	*win;
	ac = 0;
	(void)av;
	env = check_env(env);
	if (set_shell(&g_win)|| get_win_data(&g_win) || init_env(&(g_win->lstenv), env))
		return (1);
	if (!(g_win->his = (t_his *)malloc(sizeof(t_his))))
		exit(fd_printf(2, "malloc error\n"));
	init_shell();
	g_win->his->cmdl = ft_strdup("");
	g_win->his->add = 1;
	g_win->his->prev = NULL;
	g_win->his->next = NULL;
	g_win->his->len = 0;
	g_loop = 256;
	hist_read(&g_win->his, 0, -50);
	loop(g_win);
	return (g_loop);
}
