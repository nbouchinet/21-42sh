/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:01:45 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/20 11:10:15 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int		prepare_cmd(t_tok **cmd, t_env **env, t_cmdl *cmdl)
{
	int		i;
	t_ast	*ast;

	i = 0;
	ast = NULL;
	if (*cmd)
	{
		init_ast(&ast, NULL, 0);
		primary_sequence(&ast, cmd);
		mode_off(cmdl);
		stock_restore(1);
		i = job_ast(&ast, env, 1);
		close_rdir(0, 0);
		stock_restore(0);
		destroy_ast(&ast);
		mode_on(cmdl);
	}
	return (i);
}

static int		exec_part(char **line, t_env **env, t_cmdl *cmdl)
{
	int		i;
	t_tok	*cmd;

	i = 0;
	if (*line)
	{
		init_token(&cmd);
		new_parser(&cmd, *line, 0);
		restruct_lst(&cmd);
		if (new_lexercheck(&cmd))
		{
			specified_dir(&cmd);
			if (heredoc(&cmd, NULL) != -1)
				cmdl->color = prepare_cmd(&cmd, env, cmdl);
		}
		cmd ? destroy_tok(&cmd) : 0;
	}
	return (i);
}

void			lstfree(void *content, size_t type)
{
	(void)type;
	free(content);
}

static void		loop(t_cmdl *cmdl)
{
	while (42)
	{
		job_control(NULL, NULL, UPT);
		job_control(NULL, NULL, CHK);
		init_cmdl();
		get_cmdl(cmdl);
		if (cmdl->opt & CCTRLD)
			break ;
		exec_part(&cmdl->line.str, &cmdl->lstenv, cmdl);
		if (cmdl->exit != 256)
			break ;
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
	if (set_shell(cmdl) || get_win_data(cmdl) || init_env(&(cmdl)->lstenv, env))
		return (1);
	hist_session();
	loop(cmdl);
	return (cmdl->exit ? cmdl->exit : 0);
}
