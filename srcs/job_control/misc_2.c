/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 02:43:03 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/10 13:43:04 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

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
	static int		stdin = -1;
	static int		stdout = -1;
	static int		stderr = -1;

	if (mod)
	{
		stdin = dup(STDIN_FILENO);
		stdout = dup(STDOUT_FILENO);
		stderr = dup(STDERR_FILENO);
	}
	else
	{
		dup2(stdin, STDIN_FILENO);
		dup2(stdout, STDOUT_FILENO);
		dup2(stderr, STDERR_FILENO);
		close(stdin);
		close(stdout);
		close(stderr);
	}
}

int		nbr_process(t_job **job)
{
	int			i;
	t_process	*p;

	i = 0;
	p = (*job)->first_process;
	while (p)
	{
		i++;
		p = p->next;
	}
	return (i);
}

int		check_j(t_job **table, t_job **job, t_job **prev)
{
	t_job	*j;

	j = *job;
	if (check_kill(&j))
	{
		delete_tnode(&j, prev, table);
		if (*table)
		{
			*job = *table;
			*prev = NULL;
		}
		else
			return (0);
	}
	else
	{
		*prev = *job;
		*job = (*job)->next;
	}
	return (1);
}
