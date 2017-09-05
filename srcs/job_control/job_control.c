/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/16 20:14:28 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/05 17:50:39 by nbouchin         ###   ########.fr       */
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

char	*init_job_name(t_ast **ast)
{
	char	*cmd;
	t_ast	*tmp;
	t_ast	*tmp2;

	tmp = *ast;
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
	{
		cmd = ft_strjoinf(cmd, " ", 1);
		tmp2 = tmp->right->right;
		while (tmp2)
		{
			tmp2->str ? cmd = ft_strjoinf(cmd, tmp2->str, 1) : 0;
			cmd = ft_strjoinf(cmd, rdir_print(tmp2->type), 1);
			if (ft_strcmp(tmp2->left->str, "-") != 0)
				cmd = ft_strjoinf(cmd, " ", 1);
			cmd = ft_strjoinf(cmd, tmp2->left->str, 1);
			if ((tmp2 = tmp2->right))
				cmd = ft_strjoinf(cmd, " ", 1);
		}
	} // faire une partie redirection en recursive
	return (cmd);
}
