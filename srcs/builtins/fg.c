/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 15:34:15 by nbouchin          #+#    #+#             */
/*   Updated: 2017/10/04 16:30:29 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_fg(t_ast **ast, t_env **env)
{
	(void)env;
	(*ast)->right ? io_seq(&(*ast)->right->right) : 0;
	return (job_control(NULL, ast, FG));
}

int		ft_bg(t_ast **ast, t_env **env)
{
	(void)env;
	(*ast)->right ? io_seq(&(*ast)->right->right) : 0;
	return (job_control(NULL, ast, BG));
}
