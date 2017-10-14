/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 13:16:09 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/11 10:25:42 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_env		*lst_at(t_env **env, char *cmp)
{
	t_env	*tmp;

	tmp = *env;
	if (!tmp)
		return (NULL);
	while (tmp && ft_strcmp(tmp->var, cmp))
		tmp = tmp->next;
	return (tmp);
}

void		set_buff(char **git, int fd)
{
	int		i;
	char	*line;

	i = -1;
	while (get_next_line(fd, &line))
	{
		if (ft_strchr(line, '*'))
		{
			(*git) = ft_strdup(line + 2);
			ft_strdel(&line);
		}
		ft_strdel(&line);
	}
	close(fd);
}

void		get_git(char **git)
{
	int		pid;
	int		status;
	int		fd[2];
	char	*arg[3];

	if ((pipe(fd)) == -1)
		return ;
	if ((pid = fork()))
	{
		waitpid(pid, &status, WUNTRACED);
		if (WEXITSTATUS(status))
			return ;
		close(fd[1]);
	}
	else
	{
		dup2(fd[1], 1);
		dup2(fd[1], 2);
		close(fd[0]);
		arg[0] = "git";
		arg[1] = "branch";
		arg[2] = NULL;
		exit(execve("/usr/bin/git", arg, NULL));
	}
	set_buff(git, fd[0]);
}

static void	print_and_del(char **str, int w)
{
	if (!w)
	{
		fd_printf(2, "%@42sh: %s%@", H_BLUE, *str, I);
		ft_strdel(str);
	}
	else
	{
		fd_printf(2, ": %@git(%@%s%@)%@", RED, YELLOW, *str, RED, I);
		ft_strdel(str);
	}
}

void		print_prompt(void)
{
	t_cmdl	*cmdl;
	char	*buff;

	cmdl = *cmdl_slg();
	buff = NULL;
	if (!(cmdl->opt & (CSQ | CDQ | CHD)))
	{
		buff = cmdl->lstenv && lst_at(&(cmdl)->lstenv, "PWD") ?
		lst_at(&(cmdl)->lstenv, "PWD")->value : NULL;
		if (buff)
			fd_printf(2, "%@42sh: %s%@", H_BLUE, buff, I);
		else if ((buff = getcwd(buff, MAXPATHLEN)))
			print_and_del(&buff, 0);
		buff = NULL;
		get_git(&buff);
		if (buff)
			print_and_del(&buff, 1);
		write(2, "\n$> ", 4);
	}
	else if ((cmdl->opt & (CSQ | CDQ)))
		cmdl->opt & CSQ ? write(2, "\nquote> ", 8) : write(2, "\ndquote> ", 9);
	else if ((cmdl->opt & (CHD)))
		cmdl->line.pr = write(2, "heredoc> ", 9);
	cmdl->line.cur = cmdl->line.pr;
}
