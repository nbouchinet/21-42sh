/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:01:45 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/12 17:26:54 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		exec_part(char **line, t_env **env)
{
	t_ast	*ast;
	t_tok	*cmd;

	init_token(&cmd);
	new_parser(&cmd, *line);
	lexer_check(&cmd);
	expanse(&cmd, env);
	if (!cmd)
		return ;
	init_ast(&ast, NULL, 0);
	primary_sequence(&ast, &cmd);
	job_ast(&ast, env, 1);
	destroy_ast(&ast);
	destroy_tok(&cmd);
}

static void		loop(t_cmdl *cmdl)
{
	t_local		*loc;

	while (42)
	{
		job_control(NULL, NULL, UPT);
		job_control(NULL, NULL, CHK);
		init_cmdl();
		get_cmdl(cmdl);
		if (cmdl->opt & CCTRLD)
			break ;
		if (cmdl->line.str && !(cmdl->line.str[0] == '\\' &&
		cmdl->line.str[1] == 0))
		{
			mode_off(cmdl);
			exec_part(&cmdl->line.str, &cmdl->lstenv);
			mode_on(cmdl);
		}
		loc = *local_sgt(0);
		while (loc)
			loc = loc->n;
	}
	unset_shell(cmdl);
}

int				main(int ac, char *av[], char *env[])
{
	t_cmdl	*cmdl;

	ac = 0;
	(void)av;
	env = check_env(env);
	cmdl = *cmdl_slg();
	if (set_shell(cmdl) || get_win_data(cmdl) || init_env(&(cmdl->lstenv), env))
		return (1);
	loop(cmdl);
	return (cmdl->exit ? cmdl->exit : 0);
}
