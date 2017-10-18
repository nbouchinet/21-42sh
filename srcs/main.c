/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:01:45 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/18 10:55:33 by nbouchin         ###   ########.fr       */
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

void	restruct_lst(t_tok **lst);

int		new_lexercheck(t_tok **lst);


static int		exec_part(char **line, t_env **env, t_cmdl *cmdl)
{
	int		i;
	t_ast	*ast;
	t_tok	*cmd;

	i = 0;
	ast = NULL;
	if (*line)
	{
		init_token(&cmd);
		new_parser(&cmd, *line, 0);
		restruct_lst(&cmd);
		if (new_lexercheck(&cmd)) // revoir valeur binaire
		{
			specified_dir(&cmd);
			if (heredoc(&cmd) != -1)
			{
				if (cmd)
				{
					init_ast(&ast, NULL, 0);
					primary_sequence(&ast, &cmd);
					mode_off(cmdl);
//					ft_putast(ast);
					stock_restore(1);
					cmdl->ret = job_ast(&ast, env, 1);
					close_rdir(0, 0);
					stock_restore(0);
					destroy_ast(&ast);
					mode_on(cmdl);
				}
			}
		}
		destroy_tok(&cmd);
	}
	return (i);
}

void	lstfree(void *content, size_t type)
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
	// ft_putnbrl(cmdl->exit);
	return (cmdl->exit ? cmdl->exit : 0);
}
