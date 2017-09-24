/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 20:14:28 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/23 13:24:23 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*rdir_print(int type)
{
	if (type == RDIR)
		return (">");
	else if (type == BDIR)
		return ("<");
	else if (type == RRDIR)
		return (">>");
	else if (type == BBDIR)
		return ("<<");
	else if (type == AGRE)
		return (">&");
	else if (type == BGRE)
		return ("<&");
	return (NULL);
}

char	*init_rdir(char **cmd, t_ast **ast)
{
	t_ast	*tmp;

	if (*ast)
	{
		tmp = *ast;
		if (tmp->type >= RDIR && tmp->type <= BGRE)
			init_rdir(cmd, &tmp->right);
		(*cmd) = ft_strjoinf((*cmd), " ", 1);
		if (tmp->str)
			(*cmd) = ft_strjoinf((*cmd), tmp->str, 1);
		(*cmd) = ft_strjoinf((*cmd), rdir_print(tmp->type), 1);
		(*cmd) = ft_strjoinf((*cmd), " ", 1);
		(*cmd) = ft_strjoinf((*cmd), tmp->left->str, 1);
	}
	return (NULL);
}

char	*init_job_name(t_ast **ast)
{
	char	*cmd;
	t_ast	*tmp;
	t_ast	*tmp2;

	tmp = *ast;
	if (tmp->left->left)
	{
		cmd = ft_strdup(tmp->left->left->str);
		if (tmp->left->right)
		{
			cmd = ft_strjoinf(cmd, " ", 1);
			tmp2 = tmp->left->right;
			while (tmp2)
			{
				cmd = ft_strjoinf(cmd, tmp2->str, 1);
				if ((tmp2 = tmp2->right))
					cmd = ft_strjoinf(cmd, " ", 1);
			}
		}
		if (tmp->right)
			init_rdir(&cmd, &tmp->right->right);
		return (cmd);
	}
	return (NULL);
}
