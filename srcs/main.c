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

static int	unset_shell(t_win **win)
{
	(*win)->term.c_lflag |= ICANON;
	(*win)->term.c_lflag |= ECHO;
	if (tcsetattr(0, TCSADRAIN, &(*win)->term) == -1)
		return (fd_printf(2, "unset-shell: tcsetattr: ERROR\n"));
	tputs(tgetstr("am", NULL), 1, ft_putchar);
	(*win)->fd = open((*win)->hd_path, O_TRUNC);
	close((*win)->fd);
	free(*win);
	(*win)->ctrld ? ft_printf("exit\n") : 0;
	// free win->hd win->his si win->ctrld;
	*win = NULL;
	return (0);
}

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
	if (ioctl(0, TIOCGWINSZ, &w))
		return (fd_printf(2, "Error while accesing windows data\n"));
	(*win)->co = w.ws_col;
	(*win)->li = w.ws_row;
	return (0);
}

static int	set_shell(t_win **win)
{
	char			*shl_name;
	char			buff[1024];

	tputs(tgetstr("nam", NULL), 1, ft_putchar);
	if (((*win) = (t_win*)malloc(sizeof(t_win))) == NULL)
		return (1);
	if ((shl_name = getenv("TERM")) == NULL)
		shl_name = "xterm-256color";
	if (tgetent(0, shl_name) == ERR)
		return (fd_printf(2, "tgetent: ERROR\n"));
	if (tcgetattr(0, &(*win)->term) == -1)
		return (fd_printf(2, "tcgetattr: ERROR\n"));
	(*win)->term.c_lflag &= ~(ICANON);
	(*win)->term.c_lflag &= ~(ECHO);
	(*win)->term.c_cc[VMIN] = 0;
	(*win)->term.c_cc[VTIME] = 1;
	if (tcsetattr(0, TCSADRAIN, &(*win)->term) == -1)
		return (fd_printf(2, "set-shell: tcsetattr: ERROR\n"));
	(*win)->hd_path = ft_strjoinf(getcwd(buff, 1024),
	ft_strdup("/includes/hdoc/hdoc_file"), 2);
	return (0);
}

static void	exec_part(char **line, t_env **env)
{
	t_ast	*ast;
	t_tok	*cmd;
	t_tok	*tmp;

	init_token(&cmd);
	new_parser(&cmd, *line);
	tmp = cmd; 
	// while (tmp)
	// {
	// 	ft_putendl(tmp->str);
	// 	ft_putnbrl(tmp->type);
	// 	ft_putendl("=============");
	// 	tmp = tmp->next;
	// }
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
			win->term.c_lflag |= ICANON;
			win->term.c_lflag |= ECHO;
			if (tcsetattr(0, TCSADRAIN, &win->term) == -1)
				exit(1);
			exec_part(&cmd, &lstenv);
			win->term.c_lflag &= ~(ICANON);
			win->term.c_lflag &= ~(ECHO);
			if (tcsetattr(0, TCSADRAIN, &win->term) == -1)
				exit(1);
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
