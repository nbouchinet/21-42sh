/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 15:00:12 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/08 09:18:15 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#define LOW_U_FLAG	1
#define LOW_I_FLAG	2

int		check_equal(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == '=')
			return (1);
	return (0);
}

int		test(char *s)
{
	if (check_equal(s) == 1)
		return (1);
	return (0);
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
			//			ft_putendl_fd("Wait what", 2);
			return ;
		}
	}
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

int		exec_env(t_ast **ast, t_env **env, int flag)
{
	(void)env;
	(void)flag;
	t_tok	*tok;
	t_ast	*tmp;
	t_ast	*new_ast;
	char	*cmd;

	tmp = *ast;
	tok = NULL;
	cmd = recreat_cmd(&tmp);
	if (cmd != NULL)
	{
		init_token(&tok);
		new_parser(&tok, cmd);
		ft_strdel(&cmd);
		init_ast(&new_ast, NULL, 0);
		primary_sequence(&new_ast, &tok);
		delete_lst(&tok);
		//		ft_putast(new_ast);
		if ((new_ast->left->left->type == CMD_NAME_ABS ? find_bin(&new_ast->left->left) : find_rlt(&new_ast->left->left, env)) == 1)
		{
			job_ast(&new_ast, (flag & LOW_I_FLAG) ? NULL : env, 1);
			destroy_ast(&new_ast);
			// sleep(30);
		}
	} // delete ast
	return (0);
}

t_ast	*new_env(t_env **n_env, t_ast **ast, t_env **env)
{
	t_env	*tmp;
	t_env	*tmp_env;

	if (find_node(env, (*ast)->str, NULL))
	{
		if (!((*n_env) = (t_env*)malloc(sizeof(t_env))))
			return (NULL);
		tmp = *env;
		tmp_env = *n_env;
		while (tmp)
		{
			if (ft_strcmp((*ast)->str, tmp->var) != 0)
			{
				tmp_env->var = ft_strdup(tmp->var);
				tmp_env->value = ft_strdup(tmp->value);
				if (tmp->next && ft_strcmp((*ast)->str, tmp->next->var) == 0)
					tmp = tmp->next;
				if (tmp->next && ft_strcmp((*ast)->str, tmp->next->var) != 0)
				{
					if (!(tmp_env->next = (t_env*)malloc(sizeof(t_env))))
						return (NULL);
					tmp_env = tmp_env->next;
				}
			}
			tmp = tmp->next;
		}
		tmp_env->next = NULL;
	}
	return ((*ast)->right);
}

int		builtin_env(t_ast **ast, t_ast **save, t_env **env, int flag)
{
	t_ast	*tmp;

	tmp = *ast;
	while (tmp)
	{
		if (test(tmp->str) == 1)
			tmp = tmp->right;
		else
			return (exec_env(&tmp, env, flag));
	}
	(flag & LOW_I_FLAG) ? 0 : print_env(*env);
	tmp = *save;
	while (tmp)
	{
		ft_putendl(tmp->str);
		tmp = tmp->right;
	}
	return (1);
}

int		ft_enve(t_ast **ast, t_env **env)
{
	int		flag;
	t_ast	*tmp;
	t_ast	*save;
	t_env	*n_env;

	n_env = NULL;
	tmp = *ast;
	flag = 0;
	tmp = env_option(&tmp->left->right, &flag);
	if (flag != -1)
	{
		tmp = (flag & LOW_U_FLAG) ? new_env(&n_env, &tmp, env) : tmp;
		save = tmp;
		if (builtin_env(&tmp, &save, n_env ? &n_env : env, flag) == 1)
		{
			n_env ? delete_lstenv(&n_env) : 0;
			return (1);
		}
		n_env ? delete_lstenv(&n_env) : 0;
	}
	return (0);
}
