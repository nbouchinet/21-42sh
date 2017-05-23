/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 11:47:37 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/18 14:46:43 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"

void	cmd_seq(t_ast *ast)
{

	simple_command(ast->left);
	// if (tmp->right)
	// 	io_command(&tmp->right);
}

void	simple_command(t_ast *ast)
{
	ft_putendl("/// SIMP_CMD \\\\\\\\");
	ft_putendl("==branche de gauche==");
	ft_putendl(ast->left->str);
	ft_putendl("==branche de droite==");
	ast = ast->right;
	while (ast)
	{
		ft_putendl(ast->str);
		ast = ast->right;
	}
}

int		exec_oa_sequence(t_ast **ast)
{
	t_ast	*tmp;

	tmp = *ast;
	if (tmp->left->type == AND || tmp->left->type == OR)
	{
		if (exec_oa_sequence(&tmp->left) == 1)
		{
			if (tmp->left->right->type == CMD_SEQ)
			{
				ft_putendl("CMD_SEQ Found droite");
				cmd_seq(tmp->left->right); // IMPLEMENTATION IF exec_oa_sequence() == 0 ? Check rdir : cmd_seq();
				return (1);
			}
		}
		else
			ft_errormsg(NULL, NULL, "exec_oa_sequence returned 0");
	}
	if (tmp->left->type == CMD_SEQ)
	{
		ft_putendl("CMD_SEQ found");
		cmd_seq(tmp->left);
		return (1);
	}
	return (0);
}

void	simple_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_ast	*tmp_ast;

	tmp = *lst;
	tmp_ast = *ast;
	ft_putendl(tmp->str);
	init_ast(&tmp_ast->left, tmp->str, CMD_NAME);
	tmp = tmp->next;
	ft_errormsg("valeur str CMD_NAME: ", NULL, (*ast)->left->str);
	while (tmp != *sep)
	{
		init_ast(&tmp_ast->right, tmp->str, CMD_ARG);
		ft_errormsg("valeur str CMD_ARG: ", NULL, (*ast)->right->str);
		if (tmp->next != *sep)
		tmp_ast = tmp_ast->right;
		tmp = tmp->next;
	}
}

void	command_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	t_tok	*tmp;
	t_ast	*tmp_ast;

	tmp = *lst;
	tmp_ast = *ast;
	// init_ast(&tmp_ast, NULL, CMD_SEQ);
	while (tmp && tmp->type == 9)
		tmp = tmp->next;
	ft_putendl("apres boucle type 9");
	init_ast(&tmp_ast->left, NULL, SIMP_CMD);
	ft_putendl("After init SIMP_CMD");
	simple_sequence(&tmp_ast->left, lst, &tmp);
	ft_putendl("Complete simp_seq done");
	if (tmp != *sep)
	{
		init_ast(&tmp_ast->right, NULL, IO_FILE);
		// io_sequence(&tmp_ast->right, &tmp, sep); // recursive call
	}
}


t_tok	*find_andor_tok(t_tok **lst, t_tok **stop)
{
	t_tok	*tmp;

	tmp = *lst;
	while (tmp && tmp != *stop && (tmp->type != AND && tmp->type != OR))
		tmp = tmp->next;
	// else
		// while (tmp && (tmp->type != AND || tmp->type != OR))
			// tmp = tmp->next;
	return (tmp);
}

void	oa_sequence(t_ast **ast, t_tok **lst, t_tok **sep)
{
	int		i = 0;
	t_tok	*tmp;
	t_tok	*tmp_first;
	t_tok	*new_sep;
	t_ast	*tmp_ast;

	tmp_ast = *ast;
	tmp_first = *lst;
	while ((tmp = find_andor_tok(&tmp_first, sep)) != *sep)
	{
		tmp_first = tmp->next;
		new_sep = tmp;
		tmp = tmp->next;
	}
	if (tmp_first != *lst)
	{
		init_ast(&tmp_ast->left, new_sep->str, new_sep->type);
		tmp_ast = tmp_ast->left;
		init_ast(&tmp_ast->right, NULL, CMD_SEQ);
		command_sequence(&tmp_ast->right, &tmp_first, &tmp);
		oa_sequence(&tmp_ast, lst, &new_sep);
	}
	else
	{
		init_ast(&tmp_ast->left, NULL, CMD_SEQ);
		command_sequence(&tmp_ast->left, lst, sep);
	}
} // Actually Work
