/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 17:31:56 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/11 19:54:10 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
**	A supprimer
*/

// static int		init_env(t_env **lst, char **env)
// {
// 	int		i;
// 	char	**envtab;
// 	t_env	*tmp;
//
// 	i = -1;
// 	env && !env[0] ? *lst = NULL : 0;
// 	if (env && env[0])
// 		if (!(*lst = (t_env*)malloc(sizeof(t_env))))
// 			return (fd_printf(2, "malloc error\n"));
// 	tmp = *lst;
// 	while (env[++i])
// 	{
// 		envtab = ft_strsplit(env[i], '=');
// 		tmp->var = ft_strdup(envtab[0]);
// 		tmp->value = ft_strdup(envtab[1]);
// 		if (env[i + 1])
// 		{
// 			if (!(tmp->next = (t_env*)malloc(sizeof(t_env))))
// 				return (fd_printf(2, "malloc error\n"));
// 			tmp = tmp->next;
// 		}
// 		ft_free(envtab, NULL, 1);
// 	}
// 	tmp ? tmp->next = NULL : 0;
// 	return (0);
// }
//
// static void loop(t_cmdl *cmdl)
// {
// 	while (1)
// 	{
// 		init_cmdl();
// 		get_cmdl(cmdl);
// 		if (cmdl->opt & CCTRLD)
// 			break ;
// 		ft_putendl("|");
// 		ft_printf("\n\n%@%s%@\n\n", BLUE, cmdl->line.str, I);
// 	}
// 	unset_shell(cmdl);
// }
//
// int			main(int ac, char *av[], char *env[])
// {
// 	t_cmdl		*cmdl;
//
// 	(void)ac;
// 	(void)av;
// 	cmdl = *cmdl_slg();
// 	env = check_env(env);
// 	if (set_shell(cmdl) || get_win_data(cmdl) ||
// 	init_env(&cmdl->lstenv, env))
// 		return (1);
// 	loop(cmdl);
// 	return (cmdl->exit ? cmdl->exit : 0);
// }
