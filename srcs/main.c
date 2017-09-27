/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 13:01:45 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/27 15:12:04 by zadrien          ###   ########.fr       */
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
	t_ast	*ast;
	t_tok	*cmd;
	// t_tok	*tmp;
	int		i;

	i = 0;
	if (*line)
	{
		ft_putendl("6.1");
		init_token(&cmd);
		ft_putendl("6.2");
		new_parser(&cmd, *line);
		// tmp = cmd;
		// while (tmp)
		// {
		// 	ft_putendl(tmp->str);
		// 	tmp = tmp->n;
		// }
		ft_putendl("6.3");
		restruct_lst(&cmd);
		ft_putendl("6.4");
		db_lst(&cmd);
		ft_putendl("6.5");
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
				i = job_ast(&ast, env, 1);
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
		ft_putendl("0");
		job_control(NULL, NULL, UPT);
		ft_putendl("1");
		job_control(NULL, NULL, CHK);
		ft_putendl("2");
		init_cmdl();
		ft_putendl("3");
		get_cmdl(cmdl);
		ft_putendl("4");
		ft_printf("exec: %s\n", cmdl->line.str);
		if (cmdl->opt & CCTRLD)
			break ;
		ft_putendl("5");
		if (cmdl->line.str[0] && !(cmdl->line.str[0] == '\\' &&
			cmdl->line.str[1] == 0))
		{
			ft_putendl("6");
			exec_part(&cmdl->line.str, &cmdl->lstenv, cmdl);
			ft_putendl("7");
		}
		if (cmdl->exit != 256)
			break ;
		ft_putendl("8");
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
	hist_read(NULL, 0, -1, NULL);
	loop(cmdl);
	return (cmdl->exit ? cmdl->exit : 0);
}
