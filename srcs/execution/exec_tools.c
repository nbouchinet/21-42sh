/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/30 18:11:02 by zadrien           #+#    #+#             */
/*   Updated: 2017/06/30 19:43:42 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	pipe_seq(t_ast **ast, t_env **env, int i)
{
	t_ast	*tmp;

	tmp = *ast;
	if (i == 1)
	{
		if ((ft_strncmp(tmp->left->left->left->str, "./", 2) == 0) ||
			tmp->left->left->left->str[0] == '/')
			abs_cmd(&tmp->left, env);
		else
			rlt_cmd(&tmp->left, env);
	}
	else
	{
		if ((ft_strncmp(tmp->left->left->str, "./", 2) == 0) ||
			tmp->left->left->str[0] == '/')
			abs_cmd(&tmp, env);
		else
			rlt_cmd(&tmp, env);
	}
}

void	cmd_seq(t_ast **ast, t_env **env)
{
	t_ast	*tmp;

	tmp = *ast;
	if ((ft_strncmp(tmp->left->left->str, "./", 2) == 0) ||
		tmp->left->left->str[0] == '/')
		abs_cmd(&tmp, env);
	else
		rlt_cmd(&tmp, env);
}

void	cont_pipe(t_ast **ast, t_env **env, int *p)
{
	close(p[1]);
	(*ast)->right ? exec_bina(&(*ast)->right, env, p[0], PIPE_SEQ) : 0;
	close(p[0]);
}
