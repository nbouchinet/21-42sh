/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 00:31:20 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/22 14:01:05 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

t_env	*next_node(t_env **env)
{
	if (!((*env)->next = (t_env*)malloc(sizeof(t_env))))
		return (NULL);
	(*env)->next->next = NULL;
	return ((*env)->next);
}

t_ast	*env_option(t_ast **ast, int *flags)
{
	t_ast	*tmp;

	tmp = *ast;
	while (tmp && tmp->str[0] == '-')
	{
		if (tmp->str[1] != '-')
		{
			env_opt(tmp->str, flags);
			if ((*flags) == -1)
				return (NULL);
		}
		else if (tmp->str[2] == '\0')
			return (tmp->right);
		tmp = tmp->right;
	}
	return (tmp);
}

void	env_opt(char *str, int *flags)
{
	int		i;

	i = 0;
	while (str[++i])
	{
		if (str[i] == 'i')
			(*flags) |= LOW_I_FLAG;
		else
		{
			ft_putstr_fd("env : illegal option -- ", 2);
			ft_putchar_fd(str[i], 2);
			ft_putchar_fd('\n', 2);
			ft_putendl_fd("usage: env [-i] [name=value ...]\n"
						"\t   [utility [argument ...]]", 2);
			(*flags) = -1;
			return ;
		}
	}
}

int		print_error_env(int err, char *str)
{
	if (err == -1)
		ft_errormsg("env: ", NULL, "Path not set.");
	else if (err == -2)
		ft_errormsg("env: ", NULL, "Path's value not set.");
	else if (err == -3)
		ft_errormsg("env: ", str, ": Command not found.");
	else if (err == 1)
		return (1);
	return (0);
}
