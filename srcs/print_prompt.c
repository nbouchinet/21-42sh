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
		waitpid(pid, &status, WUNTRACED | WCONTINUED);
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

static void	print_and_del(char **str, int w, int ret)
{
	if (!w)
	{
		ret ? write(2, "\e[32m42sh: ", ft_strlen("\e[32m42sh: ")) :
		write(2, "\e[31m42sh: ", ft_strlen("\e[31m42sh: "));
		ft_putstr_fd(*str, 2);
		write(2, "\033[0m", 1);
		ft_strdel(str);
	}
	else if (w == 1)
	{
		write(2, " (", 2);
		write(2, "\e[94m", ft_strlen("\e[94m"));
		ft_putstr_fd(*str, 2);
		write(2, "\033[0m", ft_strlen("\033[0m"));
		write(2, ")", 1);
		ft_strdel(str);
	}
	else
	{
		ret ? write(2, "\e[32m42sh: ", ft_strlen("\e[32m42sh: ")) :
		write(2, "\e[31m42sh: ", ft_strlen("\e[31m42sh: "));
		ft_putstr_fd(*str, 2);
		write(2, "\033[0m", ft_strlen("\033[0m"));
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
			print_and_del(&buff, 2, cmdl->ret);
		else if ((buff = getcwd(buff, MAXPATHLEN)))
			print_and_del(&buff, 0, cmdl->ret);
		buff = NULL;
		get_git(&buff);
		if (buff)
			print_and_del(&buff, 1, cmdl->ret);
		write(2, "\n$> ", 4);
	}
	else if ((cmdl->opt & (CSQ | CDQ)))
		cmdl->opt & CSQ ? write(2, "\nquote> ", 8) : write(2, "\ndquote> ", 9);
	else if ((cmdl->opt & (CHD)))
		cmdl->line.pr = write(2, "heredoc> ", 9);
	cmdl->line.cur = cmdl->line.pr;
}
