/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:01:45 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/24 14:20:28 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

extern int g_loop;

static int	dup_env(char **env, char **new[])
{
	int		i;

	i = -1;
	if (!(*new = (char **)malloc(sizeof(char *) * (ft_tablen(env) + 1))))
		return (fd_printf(2, "Exiting: malloc error\n"));
	i = -1;
	while (env[++i])
		if (ft_strenv(env[i], "SHLVL") != NULL)
			(*new)[i] = ft_strjoinf("SHLVL=",
			ft_itoa(ft_atoi(&env[i][6]) + 1), 2);
		else
			(*new)[i] = ft_strdup(env[i]);
	(*new)[i] = NULL;
	return (0);
}

int			get_win_data(t_win **win)
{
	struct winsize	w;
	if (ioctl(0, TIOCGWINSZ, &w) == -1)
		return (fd_printf(2, "Error while accesing window data\n"));
	(*win)->co = w.ws_col;
	(*win)->li = w.ws_row;
	return (0);
}

static void	exec_part(char **line, t_env **env)
{
	t_ast	*ast;
	t_tok	*cmd;

	init_token(&cmd);
	new_parser(&cmd, *line);
	init_ast(&ast, NULL, 0);
	primary_sequence(&ast, &cmd);
	exec_ast(&ast, env);

}
static void	loop(char **env, t_win *win)
{
	char	*cmd;
	t_env	*lstenv;

	if (env)
		init_env(&lstenv, env);
	while (g_loop)
	{
		cmd = NULL;
		get_cmdl(&cmd, &win, NULL, env);
		if (win->ctrld)
			break ;
		if (cmd)
		{
			mode_off(&win);
			exec_part(&cmd, &lstenv);
			mode_on(&win);
			free(cmd);
		}
	}
	unset_shell(&win);
}

int         main(int ac, char *av[], char *env[])
{
	t_win	*win;
	char	**new;

	ac = 0;
	if (!env)
		return (0);
	(void)av;
	new = NULL;
	if (set_shell(&win) != 0 || get_win_data(&win) != 0 || dup_env(env, &new) != 0)
		return (1);
	if (!(win->his = (t_his *)malloc(sizeof(t_his))))
		exit(fd_printf(2, "malloc error\n"));
	win->his->cmdl = ft_strdup("");
	win->his->prev = NULL;
    win->his->next = NULL;
	win->his->len = 0;
	loop(new, win);
	return (0);
}
