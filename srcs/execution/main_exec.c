/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 13:50:32 by zadrien           #+#    #+#             */
/*   Updated: 2017/07/09 15:32:21 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	status_process(t_ast **ast, t_env **env, int type)
{
	int		status;
	t_env	*e_n;
	t_ast	*tmp;
	char	**arg;

	tmp = *ast;
	status = exec_bina(ast, env, -1, type);
	if (WIFEXITED(status) && !WEXITSTATUS(status))
	{
		if (type != PIPE_SEQ && (e_n = find_node(env, "PATH", NULL)) &&
		find_cmd_bin(&tmp->left->left, (arg = ft_strsplit(e_n->value, ':'))) == 1)
		  {
				hash(&tmp->left, PUT);
				ft_freetab(arg);
		  }
		return (1);
	}
	return (0);
}

int			exec_bina(t_ast **ast, t_env **env, int r, int type)
{
	int			p[2];
	pid_t		son;
	t_ast		*tmp;
	static int	status = 0;

	tmp = *ast;
	// type == PIPE_SEQ ? ft_putendl("PIPE_SEQ") : 0;
	type == PIPE_SEQ ? pipe(p) : 0;
	if ((son = fork()) == 0)
	{
		if (type == PIPE_SEQ)
		{
			close(p[0]);
			if (tmp->right && tmp->right->type == PIPE)
				dup2(p[1], STDOUT_FILENO);
			r != -1 ? dup2(r, STDIN_FILENO) : 0;
			pipe_seq(&tmp->right, env, tmp->right->type == PIPE ? 1 : 0);
		}
		else
			cmd_seq(&tmp, env);
	}
	else
		type == PIPE_SEQ ? cont_pipe(&tmp, env, p) : 0;
	waitpid(son, &status, WUNTRACED | WCONTINUED);
	return (status);
}

int			exec_cmd_seq(t_ast **ast, t_env **env, int type)
{
	int					i;
	t_ast				*tmp;
	static const t_cmd	cmd[8] = {{"unsetenv", &ft_unsetenv}, {"env", &ft_env},
		{"setenv", &ft_setenv}, {"cd", &ft_cd}, {"echo", &ft_echo},
		{"exit", &ft_exit}, {"history", &ft_history}, {"hash", &hashing}};

	i = -1;
	tmp = *ast;
	while (type != PIPE_SEQ && ++i < 8)
		if (ft_strcmp(cmd[i].cmd, tmp->left->left->str) == 0)
		{
			if ((cmd[i].f(&tmp, env) == 1))
				return (1);
			else
				break ;
		}
	if (type == PIPE_SEQ || i == 8)
		if (status_process(&tmp, env, type))
			return (1);
	return (0);
}

void		exec_ast(t_ast **ast, t_env **env)
{
	int					i;
	t_ast				*tmp;
	static const t_seq	seq[4] = {{QM_SEQ, &qm_seq}, {CMD_SEQ, &exec_cmd_seq},
		{PIPE_SEQ, &exec_cmd_seq}, {AND_OR, &exec_oa}};

	i = -1;
	tmp = *ast;
	while (tmp && (tmp->type == PIPE_SEQ || tmp->type == QM_SEQ ||
			tmp->type == CMD_SEQ || tmp->type == AND_OR))
	{
		i = -1;
		while (++i < 4)
			if (seq[i].type == tmp->type)
				seq[i].f(&tmp, env, tmp->type);
		tmp = tmp->right;
	}
}
