/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 13:26:01 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/12 10:32:59 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

// static void   save_input(t_read *var)
// {
// 	char	**aname;
// 	char	*bs;
//
// 	if (!var->stack)
// 		var->stack[0] = 0;
// 	if (!(var->opt & RR) && (bs = ft_strchr(var->stack, '\\')))
// 		while (*bs)
// 		{
// 			(*bs) = *(bs + 1);
// 			bs++;
// 		}
// 	if (var->opt & AR)
// 	{
// 		aname = ft_strsplit(var->stack, ' ');
// 		local(ft_strjoinf(ft_strjoin(var->local, "="), aname[0], 1));
// 		ft_free(aname, NULL);
// 		return ;
// 	}
// 	var->stack = ft_strjoinf(ft_strjoin(var->local, "="), var->stack, 3);
// 	local(var->stack);
// }
//
// static void   buf_save(char **stack, char buf[], int *i, int type)
// {
//   char *tmp;
//   static int len = 512;
//
//   if ((*i) == len)
//   {
//  tmp = *stack;
//  if (!((*stack) = (char *)malloc(sizeof(char) * (len + 512))))
//    exit(fd_printf(2, "malloc error\n"));
//  (*stack) = ft_strcpy((*stack), tmp);
//  (*stack) = ft_strcat((*stack), buf);
// 	(*i) += 1;
// 	len += 512;
//   }
//   else
// 	(*stack)[++(*i)] = !type ? buf[0] : 0;
// }
//
// static void   read_input(t_read *var, int i, int nchar)
// {
//   char buf[6];
//
//   var->stack = ft_memalloc(512);
//   while (var->time ? var->time < var->endwait  : 1)
//   {
//  ft_memset(buf, '\0', 6);
//  read(var->fd, buf, 1);
// 	if (EOT)
// 	{
// 		var->eot = 1;
// 		return ;
// 	}
// 	!(var->opt & SR) ? write(1, &buf[0], 1) : 0;
//  var->opt & NR && PRINT ? nchar += 1 : 0;
//  (PRINT && !var->delim) || (PRINT && var->delim && var->delim[0] != buf[0])
// 		    ? buf_save(&var->stack, buf, &i, 0) : 0;
//  if ((var->nchars ? var->nchars == nchar : 0) || (var->delim ? var->delim[0]
//                                                   == buf[0] : 0) || (!var->nchars && !var->delim && RETURN))
//  {
//    var->stack[i] == '\\' && !(var->opt & RR) ? write(var->fd, "$> ", 4) : 0;
//    if (!(var->stack[i] == '\\' && !(var->opt & RR)))
//    {
//      buf_save(&var->stack, buf, &i, 1);
//      return ;
//    }
//  }
//  var->time = var->time ? time(NULL) : 0;
//   }
// }

// static int  get_opt(t_read *var, char **arg, int *i)
// {
// 	int           j;
// 	int           k;
// 	static const  t_opt opt[8] = {{"a", &aname} ,{"d", &delim}, {"n", &nchars},
// 	{"p", &prompt}, {"r", &back_slash}, {"s", &silent}, {"t", &rtimeout},
// 	{"u", &fd}};
//
// 	while (arg[++(*i)])
// 	{
// 		j = 0;
// 		k = -1;
// 		while (++k < 8 && arg[(*i)][j])
// 		{
// 			j += j == 0 && arg[(*i)][j] == '-' ? 1 : 0;
// 			if (j == 0 && arg[(*i)][j] != '-')
// 			{
// 				var->local = ft_strdup(arg[(*i)]);
// 				return (0);
// 			}
// 			if (arg[(*i)][j] == opt[k].c[0])
// 			{
// 		 		if (opt[k].f(var, arg, i, ++j))
// 					return (1);
// 				if (opt[k].c[0] != 's' && opt[k].c[0] != 'r')
// 					break ;
// 				k = 0;
// 			}
// 		}
// 		if (k == 8)
// 			return (fd_printf(2, "42sh: read: -%c: invalid option\n%s\n",
// 			arg[(*i)][j], RU));
// 	}
// 	return (0);
// }

int         ft_read(t_ast **ast, t_env **env)
{
	// t_read  var;
	// char    **targ;
	// int     i;

	(void)env;
	(void)ast;
	// ft_memset(&var, 0, sizeof(t_read));
	// targ = creat_arg_env(&(*ast)->left->right);
	// i = -1;
	// if (targ && get_opt(&var, targ, &i))
	// 	return (0);
	// !var.local ? var.local = ft_strdup("REPLY") : 0;
	// read_input(&var, -1, 0);
	// save_input(&var);
	// ft_free(targ, NULL);
	// var.delim ? ft_strdel(&var.delim) : 0;
	// var.local ? ft_strdel(&var.local) : 0;
	// var.stack ? ft_strdel(&var.stack) : 0;
	// var.eot ? write(1, "\n", 1) : 0;
	return (0);
}
