/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_seq.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/20 11:21:15 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/24 14:23:53 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

typedef struct		s_cmd
{
	char			*cmd;
	int			(*f)(t_ast**, t_env**);
}					t_cmd;

t_env	*find_node(t_env **env, char *var, char *value)
{
	t_env	*tmp;

	tmp = *env;
	if (var != NULL)
		while (tmp && ft_strcmp(tmp->var, var) != 0)
			tmp = tmp->next;
	else
		while (tmp && ft_strcmp(tmp->value, value) != 0)
			tmp = tmp->next;
	return (tmp);
}

int		exec_cmd_seq(t_ast **ast, t_env **env) // Keep the path ?
{
	int			i;
	t_ast		*tmp;
	static const t_cmd	cmd[3] = {{"unsetenv", &ft_unsetenv}, {"env", &ft_env},
					 {"setenv", &ft_setenv}}; //{"unsetenv", &ft_unsetenv},
							// {"setenv", &ft_setenv}, {"cd", &ft_cd}};

	i = -1;
	tmp = *ast;
	while (++i < 3)
		if (ft_strcmp(cmd[i].cmd, tmp->left->str) == 0)
			if (cmd[i].f(&tmp, env) == 1)
				return (1);
	if (i == 3)
		if (exec_binary(&tmp, env))
			return (1);
	return (0);
}

char	**creat_arg(t_ast **ast, char *cmd)
{
	int		i;
	int		j;
	char	**arg;
	t_ast	*tmp;

	i = 0;
	tmp = NULL;
	if ((i = count_arg_node(&(*ast)) + 1) >= 2)
		tmp = *ast;
	if (!(arg = (char**)malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	arg[0] = ft_strdup(cmd);
	j = 1;
	while (tmp && j < i + 1)
	{
		arg[j] = ft_strdup(tmp->str);
		tmp = tmp->right;
		j++;
	}
	arg[i] = NULL;
	return (arg);
}

int		time_4_magic(char **arg, char **env)
{
	// int		i = -1;
	int		status;
	pid_t	son;

	son = fork();
	if (son == 0)
		execve(arg[0], arg, env);
	else
	{
		arg ? ft_freetab(arg) : 0;
		env ? ft_freetab(env) : 0;
		if (waitpid(son, &status, WUNTRACED | WCONTINUED) &&
		WIFSIGNALED(status) && WTERMSIG(status) == 2)
			write(1, "\n", 1);
		if (WIFEXITED(status) && !WEXITSTATUS(status))
			return (1);
	}
	return (0);
}

int		exec_abs_cmd(t_ast **ast, t_env **env)
{
	char	**arg;
	char	**env_tab;

	if (find_bin(&(*ast)->left) == 1)
	{
		arg = creat_arg(&(*ast)->right, (*ast)->left->str);
		env ?  (env_tab = get_env(env, (*ast)->left->str)) : (env_tab = NULL);
		if (time_4_magic(arg, env_tab) == 1)
		{
			reduc_shlvl(env, (*ast)->left->str);
			// free((*ast)->left->str); // Faire fonction de free AST
			return (1);
		}
		else
			return (0); // Assugeti a des leaks
	}
	else
		ft_errormsg("21sh: ", (ft_strrchr((*ast)->left->str, '/') + 1), ": Command not found.");
	return (0);
}

int		exec_rlt_cmd(t_ast **ast, t_env **env)
{
	t_env	*path_node;
	char	**path;
	char	**arg;
	char	**env_tab;

	arg = NULL;
	env_tab = NULL;
	path = NULL;
	if (!(path_node = find_node(env, "PATH", NULL)))
		ft_errormsg("21sh:", NULL, "PATH not set.");
	else if ((path = ft_strsplit(path_node->value, ':')) && find_cmd_bin(&(*ast)->left, path) == 1)
	{
		arg = creat_arg(&(*ast)->right, (*ast)->left->str);
		if (env)
			env_tab = get_env(env, (ft_strrchr((*ast)->left->str, '/') + 1));
		if (time_4_magic(arg, env_tab) == 1)
		{
			ft_freetab(path);
			return (1);
		} // Assugeie a des leaks
	}
	else
		ft_errormsg("21sh: ", (*ast)->left->str, ": Command not found.");
	path ? ft_freetab(path) : 0;
	return (0);
}

int		exec_binary(t_ast **ast, t_env **env)
{
	if (ft_strncmp((*ast)->left->str, "./", 2) == 0 || (*ast)->left->str[0] == '/')
	{
		if (exec_abs_cmd(ast, env) == 1)
			return (1);
	}
	else
		if (exec_rlt_cmd(ast, env) == 1)
			return (1);
	return (0);
}
