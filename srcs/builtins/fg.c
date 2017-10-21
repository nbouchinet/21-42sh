/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 15:34:15 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/19 13:40:03 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_fg(t_ast **ast, t_env **env)
{
	(void)env;
	(*ast)->right ? io_seq(&(*ast)->right->right, 1) : 0;
	return (job_control(NULL, ast, FG));
}

int		ft_bg(t_ast **ast, t_env **env)
{
	(void)env;
	(*ast)->right ? io_seq(&(*ast)->right->right, 1) : 0;
	return (job_control(NULL, ast, BG));
}
