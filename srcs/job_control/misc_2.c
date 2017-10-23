/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 02:43:03 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/23 17:14:13 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		check_exit(t_job **job, t_ast **ast, t_job **table)
{
	t_cmdl	*cmdl;

	(void)ast;
	(void)job;
	cmdl = *(cmdl_slg());
	if (!cmdl->job)
		if (*table)
		{
			cmdl->job = 1;
			ft_errormsg("42sh: ", "job still running", " WATCH OUT WATCH OUT.");
			return (1);
		}
	cmdl->job = 0;
	return (0);
}

int		countnode(t_env *env)
{
	int		i;

	i = 0;
	if (!env)
		return (i);
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	*var_value(int i, char *var, char *value)
{
	char *str;

	if (!(str = (char*)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	ft_bzero(str, i + 2);
	ft_strcat(str, var);
	ft_strcat(str, "=");
	value ? ft_strcat(str, value) : 0;
	return (str);
}

void	stock_restore(int mod)
{
	int				i;
	static t_std	std[3] = {{-1, STDIN_FILENO}, {-1, STDOUT_FILENO},
								{-1, STDERR_FILENO}};

	i = -1;
	if (mod)
	{
		while (++i < 3)
			std[i].fd = dup(std[i].std);
	}
	else
		while (++i < 3)
			if (std[i].fd != -1)
			{
				dup2(std[i].fd, std[i].std);
				close(std[i].fd);
				std[i].fd = -1;
			}
}
