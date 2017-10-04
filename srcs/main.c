/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:01:45 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/04 14:10:37 by zadrien          ###   ########.fr       */
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


void	db_lst(t_tok **lst)
{
	t_tok *tmp;
	t_tok *prev;

	if (*lst)
	{
		prev = NULL;
		tmp = *lst;
		while (tmp)
		{
			if (prev)
				tmp->p = prev;
			prev = tmp;
			tmp = tmp->n;
		}
	}
}

static int		exec_part(char **line, t_env **env, t_cmdl *cmdl)
{
	int		i;
	t_ast	*ast;
	t_tok	*cmd;
	t_tok	*t;

	i = 0;
	ast = NULL;
	if (*line)
	{
		init_token(&cmd);
		new_parser(&cmd, *line);
		restruct_lst(&cmd);
		t = cmd;
		while (t)
		{
			ft_printf("%s | %d\n", t->str, t->type);
			t = t->n;
		}
		db_lst(&cmd);
		if (new_lexercheck(&cmd) == 1) // revoir valeur binaire
		{
			specified_dir(&cmd);
			heredoc(&cmd);
			expanse(&cmd, env);
			if (cmd)
			{
				init_ast(&ast, NULL, 0);
				primary_sequence(&ast, &cmd);
				ft_putast(ast);
				mode_off(cmdl);
				stock_restore(1);
				if ((i = job_ast(&ast, env, 1)))
					ft_putendl_fd("Success", 2);
				else
					ft_putendl_fd("Failure", 2);
				stock_restore(0);
				destroy_ast(&ast);
				mode_on(cmdl);
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
		// cmdl->line.str ? ft_printf("exec: %s\n", cmdl->line.str) : 0;
		if (cmdl->opt & CCTRLD)
			break ;
		if (cmdl->line.str[0] && !(cmdl->line.str[0] == '\\' &&
			cmdl->line.str[1] == 0))
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
