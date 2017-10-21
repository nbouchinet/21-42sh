/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/18 13:26:01 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/21 17:38:48 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void		save_input(t_read *v, char *stack)
{
	char	**words;
	int		i;
	int		j;

	words = ft_strsplit(stack, ' ');
	i = -1;
	while (v->local[++i] && words[i])
		if (words[i] && (v->local[i] = ft_strjoinf(v->local[i], words[i], 1)))
			local(v->local[i]);
	if (words[i])
	{
		j = i - 1;
		v->local[j] = ft_strjoinf(v->local[j], " ", 1);
		while (words[i])
		{
			v->local[j] = ft_strjoinf(v->local[j], words[i], 1);
			if (words[i + 1])
				v->local[j] = ft_strjoinf(v->local[j], " ", 1);
			i++;
		}
		local(v->local[j]);
	}
	if (words)
		ft_freetab(words);
}

void		handle_c(int sig)
{
	t_cmdl	*cmdl;

	(void)sig;
	cmdl = *cmdl_slg();
	cmdl->opt |= RRET;
}

static int	buf_save(char **stack, char buf[], int *len)
{
	char		*tmp;
	int			i;

	i = (int)ft_strlen(*stack);
	if (i == *len - 1)
	{
		*len += 512;
		tmp = ft_strdup(*stack);
		ft_strdel(&*stack);
		if (!(*stack = ft_memalloc(*len)))
			exit(EXIT_FAILURE);
		*stack = ft_strcpy(*stack, tmp);
		*stack = ft_strcat(*stack, buf);
		ft_strdel(&tmp);
	}
	else
		*stack = ft_strcat(*stack, buf);
	return (1);
}


static int	rbs(t_read *v, char *stack, int c)
{
	int		nbr;

	if ((v->opt & RR) || stack[c] != '\\')
		return (0);
	nbr = 0;
	while (stack[c] == '\\')
	{
		nbr++;
		c--;
	}
	if (nbr % 2)
		return (write(1, "\n$> ", 4));
	return (0);
}

void		read_input(t_read *v, char *stack, char buf[])
{
	int		len;

	len = 512;
	while (v->time ? v->time < v->endwait : 1)
	{
		if ((*cmdl_slg())->opt & RRET && (write(1, "\n", 1)))
			break ;
		ft_memset(buf, '\0', 6);
		read(v->fd, buf, 1);
		if (CTRL_D(buf) && (v->eot = 1))
			break ;
		!(v->opt & SR) ? write(1, &buf[0], 1) : 0;
		v->opt & NR && PRINT(buf) ? v->nchars-- : 0;
		(PRINT(buf) && !v->delim) || (PRINT(buf) && v->delim && v->delim[0] !=
		buf[0]) ? buf_save(&stack, buf, &len) : 0;
		if ((v->opt & NR && !v->nchars) || (v->delim ? v->delim[0] == buf[0] : 0
		) || (!(v->opt & NR) && !(v->opt & DR) && RETURN(buf) && !rbs(v, stack,
		ft_strlen(stack) - (*stack ? 1 : 0))))
				break ;
		v->time = v->time ? time(NULL) : 0;
	}
	*stack ? save_input(v, stack) : 0;
	ft_strdel(&stack);
}
