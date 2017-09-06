/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 14:52:51 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/06 14:55:26 by zadrien          ###   ########.fr       */
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

int		find_rlt(t_ast **cmd, t_env **env)
{
	t_env	*path;
	char	**value;

	path = NULL;
	if (env && !(path = find_node(env, "PATH", NULL)))
		return (ft_errormsg("21sh: ", NULL, "PATH not set"));
	if (find_cmd_bin(cmd, (value = ft_strsplit(path->value, ':'))) == 0)
	{
		ft_freetab(value);
		return (ft_errormsg("21sh: ", (*cmd)->str, ": Command not found."));
	}
	ft_freetab(value);
	(*cmd)->type = CMD_NAME_ABS;
	return (1);
}

char	*recreat_cmd(t_ast **ast)
{
	t_ast	*tmp;
	char	*new_cmd;

	tmp = *ast;
	new_cmd = ft_strdup(tmp->str);
	(tmp = tmp->right) ? new_cmd = ft_strjoinf(new_cmd, " ", 1) : 0;
	while (tmp)
	{
		new_cmd = ft_strjoinf(new_cmd, tmp->str, 1);
		if ((tmp = tmp->right))
			new_cmd = ft_strjoinf(new_cmd, " ", 1);
	}
	return (new_cmd);
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
		else if (str[i] == 'u')
			(*flags) |= LOW_U_FLAG;
		else
		{
			ft_putstr_fd("env : illegal option -- ", 2);
			ft_putchar_fd(str[i], 2);
			ft_putendl_fd("", 2);
			(*flags) = -1;
			ft_putendl_fd("Wait what", 2);
			return ;
		}
	}
}
