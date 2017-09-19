/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:01:45 by khabbar           #+#    #+#             */

/*   Updated: 2017/09/19 14:47:32 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	ft_rec_putbtreestr(t_ast *r, int l)
{
	if (r)
	{
		printf("t: %d |%s|\n", r->type, r->str);
		if (r->left)
		{
			printf("%*c|-left--: ", (l + 1) * 2, ' ');
			ft_rec_putbtreestr(r->left, l + 1);
		}
		if (r->right)
		{
			printf("%*c|-right-: ", (l + 1) * 2, ' ');
			ft_rec_putbtreestr(r->right, l + 1);
		}
	}
}

void		ft_putast(t_ast *root)
{
	ft_rec_putbtreestr(root, 0);
}

static void		exec_part(char **line, t_env **env, t_cmdl *cmdl)
{
	t_ast	*ast;
	t_tok	*cmd;
	// t_tok	*tmp;

	if (!*line)
		return ;
	init_token(&cmd);
	new_parser(&cmd, *line);
	// tmp = cmd;
	specified_dir(&cmd);
	// while (tmp)
	// {
	// 	ft_printf("%s %d\n", tmp->str, tmp->type);
	// 	tmp = tmp->n;
	// }
	heredoc(&cmd);
	// lexer_check(&cmd); A REVOIR DE TOUTE URGENCE
	expanse(&cmd, env);
	if (!cmd)
		return ;
	init_ast(&ast, NULL, 0);
	primary_sequence(&ast, &cmd);
	//ft_putast(ast);
	ft_putchar('\n');
	mode_off(cmdl);
	job_ast(&ast, env, 1);
	destroy_ast(&ast);
	mode_on(cmdl);
	destroy_tok(&cmd);
}

void	lstfree(void *content, size_t type)
{
	(void)type;
	free(content);
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
		if (cmdl->line.str[0] && !(cmdl->line.str[0] == '\\' &&
		                           cmdl->line.str[1] == 0))
			exec_part(&cmdl->line.str, &cmdl->lstenv, cmdl);
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
	if (set_shell(cmdl) || get_win_data(cmdl) || init_env(&(cmdl)->lstenv, env))
		return (1);
	loop(cmdl);
	return (cmdl->exit ? cmdl->exit : 0);
}
