/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:01:45 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/12 12:08:51 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void     exec_part(char **line, t_env **env)
{
	t_ast   *ast;
	t_tok   *cmd;

	init_token(&cmd);
	ft_putendl("0");
	new_parser(&cmd, *line);
	ft_putendl("1");
	lexer_check(&cmd);
	ft_putendl("2");
	expanse(&cmd, env);
	ft_putendl("3");
	if (!cmd)
		return ;
	ft_putendl("4");
	init_ast(&ast, NULL, 0);
	ft_putendl("5");
	primary_sequence(&ast, &cmd);
	//      ft_putast(ast);
	job_ast(&ast, env, 1);
	// exec_ast(&ast, env);
	destroy_ast(&ast);
	destroy_tok(&cmd);
}

static void     loop(t_cmdl *cmdl)
{
	while (42)
	{
		job_control(NULL, NULL, UPT); // AST NULL
		job_control(NULL, NULL, CHK);
		init_cmdl();
		get_cmdl(cmdl);
		// ft_printf("exec: %s\n", cmdl->line.str);
		if (cmdl->opt & CCTRLD)
			break ;
		if (cmdl->line.str[0] && !(cmdl->line.str[0] == '\\' &&
		cmdl->line.str[1] == 0) && !only_space(cmdl, 0, 0))
		{
			ft_putendl(cmdl->line.str);
			mode_off(cmdl);
			exec_part(&cmdl->line.str, &cmdl->lstenv);
			mode_on(cmdl);
		}
		if (cmdl->exit != 256)
			break ;
	}
	unset_shell(cmdl);
}

int         main(int ac, char *av[], char *env[])
{
	t_cmdl	*cmdl;

	ac = 0;
	(void)av;
	env = check_env(env);
	cmdl = *cmdl_slg();
	if (set_shell(cmdl) || get_win_data(cmdl) || init_env(&(cmdl->lstenv), env))
		return (1);
	hist_read(NULL, 0, -1, NULL);
	loop(cmdl);
	return (cmdl->exit ? cmdl->exit : 0);
}
