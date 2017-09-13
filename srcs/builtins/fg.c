/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <nbouchin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 15:34:15 by nbouchin          #+#    #+#             */
/*   Updated: 2017/09/13 09:09:23 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_fg(t_ast **ast, t_env **env)
{
	(void)env;
	(void)ast;
	job_control(NULL, ast, FG);
	return (1);
}

int		ft_bg(t_ast **ast, t_env **env)
{
	(void)env;
	(void)ast;
	job_control(NULL, ast, BG);
	return (1);
}
