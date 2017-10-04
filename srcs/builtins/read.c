/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <khabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 13:26:01 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/27 15:01:49 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void   save_input(t_read *var)
{
	char	**aname;
	char	*bs;

	if (!var->stack)
		var->stack[0] = 0;
	if (!(var->opt & RR) && (bs = ft_strchr(var->stack, '\\')))
		while (*bs)
		{
			(*bs) = *(bs + 1);
			bs++;
		}
	if (var->opt & AR)
	{
		aname = ft_strsplit(var->stack, ' ');
		local(ft_strjoinf(ft_strjoin(var->local, "="), aname[0], 1));
		ft_free(aname, NULL, 1);
		return ;
	}
	var->stack = ft_strjoinf(ft_strjoin(var->local, "="), var->stack, 3);
	local(var->stack);
}

static int   buf_save(char **stack, char buf[], int *i, int type)
{
	char 		*tmp;
	static int 	len = 512;

	if ((*i) == len)
	{
		tmp = *stack;
		if (!((*stack) = (char *)malloc(sizeof(char) * (len + 512))))
			exit(fd_printf(2, "malloc error\n"));
		(*stack) = ft_strcpy((*stack), tmp);
		(*stack) = ft_strcat((*stack), buf);
		(*i) += 1;
		len += 512;
	}
	else
		(*stack)[++(*i)] = !type ? buf[0] : 0;
	return (1);
}

void handle_c(int sig)
{
	t_cmdl	*cmdl;

	(void)sig;
	cmdl = *cmdl_slg();
	cmdl->opt |= RRET;
}

int   read_input(t_read *var, int i, int nchar, char buf[])
{
	var->stack = ft_memalloc(512);
	while (var->time ? var->time < var->endwait  : 1)
	{
		if ((*cmdl_slg())->opt & RRET && (write(1, "\n", 1)))
			return (1);
		ft_memset(buf, '\0', 6);
		read(var->fd, buf, 1);
		if (CTRL_D(buf) && (var->eot = 1))
			return (1);
		!(var->opt & SR) ? write(1, &buf[0], 1) : 0;
		var->opt & NR && PRINT(buf) ? nchar += 1 : 0;
		(PRINT(buf) && !var->delim) || (PRINT(buf) && var->delim &&
		var->delim[0] != buf[0]) ? buf_save(&var->stack, buf, &i, 0) : 0;
		if ((var->nchars ? var->nchars == nchar : 0) || (var->delim ?
		var->delim[0] == buf[0] : 0) || (!var->nchars && !var->delim &&
		RETURN(buf)))
		{
			var->stack[i] == '\\' && !(var->opt & RR) ? write(var->fd, "$> ", 3)
			: 0;
			if (!(var->stack[i] == '\\' && !(var->opt & RR)))
			 	return (buf_save(&var->stack, buf, &i, 1));
		}
		var->time = var->time ? time(NULL) : 0;
	}
	return (1);
}
