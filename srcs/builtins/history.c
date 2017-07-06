/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/25 14:49:33 by khabbar           #+#    #+#             */
/*   Updated: 2017/06/30 17:54:43 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	delete_his(t_his **his)
{
	t_his 	*tmp;
	t_his	*save;

	tmp = *his;
	if (!tmp)
		return ;
	while (tmp)
	{
		save = tmp->next;
		ft_strdel(&tmp->cmdl);
		free(tmp);
		tmp = save;
	}
	if (!((*his) = (t_his *)malloc(sizeof(t_his))))
		exit(fd_printf(2, "malloc error\n"));
	(*his)->cmdl = ft_strdup("");
	(*his)->prev = NULL;
	(*his)->next = NULL;
	(*his)->len = 0;
}

static void	exec_hist(int opt, int offset, t_his *his, int len)
{
	int		nbr;
	t_his	*save_prev;

	(void)offset;
	nbr = 0;
	if (!opt && (!offset || offset > len))
		while (his && ft_strcmp(his->cmdl, ""))
		{
			ft_printf("    %d  %s\n", ++nbr, his->cmdl);
			his = his->next;
		}
	else if (!opt && offset)
	{
		while (--len)
		{
			his = his->next;
			nbr += 1;
		}
		while (his && offset--)
		{
			his = his->prev;
			nbr -= 1;
		}
		while (his && ft_strcmp(his->cmdl, ""))
		{
			ft_printf("    %d  %s\n", ++nbr, his->cmdl);
			his = his->next;
		}
	}
	else if (opt & C)
		delete_his(&his);
	else if (opt & D)
	{
		while (--offset)
		{
			save_prev = his;
			his = his->next;
		}
		ft_putendl(his->cmdl);
		ft_putendl(save_prev->cmdl);
		ft_strdel(&his->cmdl);
		save_prev->next = his->next;
		his->next->prev = save_prev;
		free(his);
	}
}

static int	is_digit(char *str)
{
	int		i;

	i = -1;
	if (str[0] == 0)
		return (1);
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

static int  get_opt(char **arg, int *opt, int *offset)
{
	int     i;
	int     j;

	i = -1;
	while (arg[++i])
	{
		j = 0;
		if (arg[i][0] == '-' && ((arg[i][1] == '-' && arg[i][2] == 0)
		|| arg[i][1] == 0))
			return (0);
		if (arg[i][0] == '-')
			while (arg[i][++j])
			{
				arg[i][j] == 'c' ? (*opt) |= C : 0;
				if (arg[i][j] == 'd')
				{
					(*opt) |= D;
					if (is_digit(arg[i] + (j + 1)))
						(*offset) = ft_atoi(arg[i] + (j + 1));
					else
						return (fd_printf(2, "history: %s: %s\n",
						arg[i] + (j + 1), HIS_MSG));
					break ;
				}
				arg[i][j] == 'a' ? (*opt) |= A : 0;
				arg[i][j] == 'n' ? (*opt) |= N : 0;
				arg[i][j] == 'r' ? (*opt) |= R : 0;
				arg[i][j] == 'w' ? (*opt) |= W : 0;
				arg[i][j] == 'p' ? (*opt) |= P : 0;
				arg[i][j] == 's' ? (*opt) |= S : 0;
				if (!ft_strchr("cdanrwps", arg[i][j]))
					return (fd_printf(2, "history: -%c: invalid option\n%s",
					arg[i][j], HIS_USAGE));
			}
		else
		{
			if (is_digit(arg[i]))
				(*offset) = ft_atoi(arg[i]);
			else
				return (fd_printf(2, "history: %s: %s\n", arg[i], HIS_MSG));
		}
	}
	return (0);
}

int         ft_history(t_ast **ast, t_env **env)
{
	char	**targ;
	int		opt;
	int		offset;
	t_his	*his;

	(void)env;
	opt = 0;
	offset = 0;
	his = win_sgt()->his;
	while (his->prev)
		his = his->prev;
	targ = creat_arg_env(&(*ast)->left->right);
	if ((targ && get_opt(targ, &opt, &offset)))
		return (0);
	ft_printf("opt: %d\noffset: %d\n", opt, offset);
	if (opt != 0 && opt != 1 && opt != 2 && opt != 3 &&  opt != 60 && opt != 190)
	{
		fd_printf(2, "%s", HIS_USAGE);
		return (0);
	}
	exec_hist(opt, offset, his, lst_len(his));
	return (1);
}