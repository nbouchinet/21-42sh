/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_pipe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 10:33:07 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/08 11:41:13 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int			exec_pro_pipe(t_process **p, t_env **env, t_job **job)
{
	char	**n_env;

	n_env = get_env(env, (*p)->argv[0]);
	if (!((*p)->pid = fork()))
	{
		execve((*p)->argv[0], (*p)->argv, n_env);
		exit(EXIT_SUCCESS);
	}
	else
	{
		(*job)->pgid = (*p)->pid;
		waitpid((*p)->pid, &(*p)->status, WUNTRACED | WCONTINUED);
	}
	ft_freetab(n_env);
	return ((*p)->status);
}

int			exec_job_pipe(t_job **job, t_env **env, int foreground)
{
	int		status;

	(void)foreground;
	status = exec_pro_pipe(&(*job)->first_process, env, job);
	mark_process_status(job);
	if (return_exec(status))
		return (1);
	return (0);
}

int		exec_env_pipe(t_ast **ast, t_env **env, t_env **r_env)
{
	int		i;
	t_tok	*tok;
	t_ast	*tmp;
	t_ast	*new_ast;
	char	*cmd;

	i = 0;
	tmp = *ast;
	tok = NULL;
	if ((cmd = recreat_cmd(&tmp)))
	{
		tok = init_tok(&tok, C);
		new_parser(&tok, cmd);
		ft_strdel(&cmd);
		init_ast(&new_ast, NULL, 0);
		primary_sequence(&new_ast, &tok);
		delete_lst(&tok);
		if ((new_ast->left->left->type == CMD_NAME_ABS ?
			find_bin(&new_ast->left->left) :
				find_rlt(&new_ast->left->left, r_env)) == 1)
			i = pipe_builtin(&new_ast, env, 1);
		destroy_ast(&new_ast);
	}
	return (i);
}

int		env_builtin_pipe(t_ast **ast, t_env **env, t_env **r_env)
{
	t_ast	*tmp;

	tmp = *ast;
	if (tmp)
		return (exec_env_pipe(&tmp, env, r_env));
	if (env)
		print_env(*env);
	return (1);
}

int		env_pipe(t_ast **ast, t_env **env)
{
	int		flag;
	t_ast	*tmp;
	t_env	*n_env;

	n_env = NULL;
	tmp = *ast;
	flag = 0;
	(*ast)->right ? io_seq(&(*ast)->right->right) : 0;
	tmp = env_option(&tmp->left->right, &flag);
	if (flag != -1)
	{
		tmp = new_env(&n_env, &tmp, env, flag);
		if (env_builtin_pipe(&tmp, &n_env, env) == 1)
		{
			n_env ? delete_lstenv(&n_env) : 0;
			return (1);
		}
		n_env ? delete_lstenv(&n_env) : 0;
	}
	return (0);
}

int			pipe_builtin(t_ast **ast, t_env **env, int foreground)
{
	int					i;
	t_job				*job;
	t_ast				*tmp;
	static const t_cmd	cmd[14] = {{"unsetenv", &ft_unsetenv},
{"hash", &hashing}, {"setenv", &ft_setenv}, {"env", &env_pipe},
{"jobs", &inter_job}, {"fg", &ft_fg}, {"cd", &ft_cd}, {"echo", &ft_echo},
{"exit", &ft_exit}, {"history", &ft_history}, {"bg", &ft_bg},
{"read", &ft_read}, {"unset", &ft_unset}, {"export", &ft_export}};

	i = -1;
	tmp = *ast;
	while (++i < 14)
		if (tmp->left->left && !ft_strcmp(cmd[i].cmd, tmp->left->left->str))
			return (cmd[i].f(&tmp, env));
	if (init_job(&job) && (job->command = init_job_name(ast)))
	{
		if (!init_process(ast, &(job)->first_process, env))
			return (delete_job(&job));
		return (exec_job_pipe(&job, env, foreground));
	}
	return (0);
}
