/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:01:45 by khabbar           #+#    #+#             */
/*   Updated: 2017/04/24 13:01:55 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/header.h"

extern int g_loop;

static int	unset_shell(t_win **win)
{
	(*win)->term.c_lflag |= ICANON;
	(*win)->term.c_lflag |= ECHO;
	if (tcsetattr(0, TCSADRAIN, &(*win)->term) == -1)
		return (fd_printf(2, "unset-shell: tcsetattr: ERROR\n"));
	tputs(tgetstr("am", NULL), 1, ft_putchar);
	free(*win);
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

static int	get_win_data(t_win **win)
{
	if (((*win)->co = tgetnum("co")) == -1)
		return (1);
	if (((*win)->li = tgetnum("li")) == -1)
		return (1);
	return (0);
}

static int	set_shell(t_win **win)
{
	char			*shl_name;

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
	return (0);
}

static void	loop(char **env, t_win *win)
{
	char	*cmd;
	t_lex	*head;

	while (g_loop)
	{
		head = NULL;
		cmd = NULL;
		get_cmdl(&cmd, &win, NULL, env);
		if (win->ctrld)
			break ;
	}
	unset_shell(&win);
}

int         main(int ac, char *av[], char *env[])
{
	t_win	*win;
	char	**new;

	ac = 0;
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