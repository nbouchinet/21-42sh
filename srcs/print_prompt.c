/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_promt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 13:16:09 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/11 20:06:05 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
**	A supprimer
*/

t_env 		*lst_at(t_env **env, char *cmp)
{
	t_env	*tmp;

	tmp = *env;
	if (!tmp)
		return (NULL);
	while (tmp && ft_strcmp(tmp->var, cmp))
			tmp = tmp->next;
	return (tmp);
}

void        set_buff(char **git, int fd)
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
}

void        get_git(char **git, int status)
{
    int		pid;
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
        execve("/usr/bin/git", arg, NULL);
		exit (0);
    }
    set_buff(git, fd[0]);
}

void     print_prompt(void)
{
    t_cmdl	*cmdl;
    char	buff[1024];
    char	*git;
	char	*pwd;

	cmdl = *cmdl_slg();
    git = NULL;
    get_git(&git, 0);
	pwd = cmdl->lstenv ? lst_at(&(cmdl)->lstenv, "PWD")->value : NULL;
    if (pwd)
        ft_printf("\%@42sh: %s%@",
        H_BLUE, pwd, I);
    else if (getcwd(buff, 1024))
        ft_printf("%@42sh %s\n%@", H_BLUE, buff, I);
    if (git)
        ft_printf(": %@git(%@%s%@)%@", RED, YELLOW, git, RED, I);
    if (!(cmdl->opt & (CSQ | CDQ)))
        write(1, "\n$> ", 4);
    else if ((cmdl->opt & (CSQ | CDQ)))
        cmdl->opt & CSQ ? write(1, "\nquote> ", 8) : write(1, "\ndquote> ", 9);
	git ? ft_strdel(&git) : 0;
}
