/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/09 16:11:48 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/22 14:14:37 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		set_exiting_value(t_cmdl *cmdl, int r_value)
{
	if (cmdl->ret != 0 && cmdl->ret != 256)
		cmdl->ret += 128;
	else if (cmdl->ret == 256)
		cmdl->ret -= 255;
	cmdl->exit = cmdl->ret;
	return (r_value);
}

int		ft_exit(t_ast **ast, t_env **env)
{
	int		i;
	t_cmdl	*cmdl;
	t_ast	*t;

	(*ast)->right ? io_seq(&(*ast)->right->right, 1) : (void)env;
	job_control(NULL, NULL, EXT);
	cmdl = *cmdl_slg();
	if (cmdl->job == 1)
		return (0);
	hash(NULL, NULL, CLEAN);
	if ((i = count_opt(&(*ast)->left->right)) > 1 &&
		fd_printf(2, "42sh: exit: too many arguments\n"))
		return (0);
	else if (i == 0)
		return (set_exiting_value(cmdl, 1));
	i = -1;
	t = (*ast)->left->right;
	while (t->str[++i])
		if (!ft_isdigit(t->str[i]) &&
		fd_printf(2, "42sh: exit: %@: numeric argument required\n", t->str))
			return (((cmdl->exit = 255) > 0 ? 0 : 0));
	cmdl->exit = ft_atoi(t->str);
	while (cmdl->exit > 255 || cmdl->exit < 0)
		cmdl->exit = (cmdl->exit > 255 ? cmdl->exit - 256 : cmdl->exit + 256);
	return (1);
}
