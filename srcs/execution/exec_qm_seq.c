/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_qm_seq.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 14:09:08 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/26 14:09:19 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int     exec_qm_seq(t_ast **ast, t_env **env)
{
	t_ast	*tmp;

    tmp = *ast;
    if (tmp->left->type == QM)
    {
        exec_qm_seq(&tmp->left, env);
        exec_ast(&tmp->left->right, env);
    }
    else
	   exec_ast(&tmp->left, env);
    return (1);
}