/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/13 14:05:48 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/13 14:05:55 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void   process_mod(char **tmp, t_bang *b, int i, char *ptr)
{
	char        **arr;

	b->mod & HB && (ptr = ft_strchr(*tmp, '/')) ? (*ptr) = 0 : 0;
	b->mod & RB && (ptr = ft_strchr(*tmp, '.')) ? (*ptr) = 0 : 0;
	b->mod & QB ? (*tmp) = ft_strjoinf(ft_strjoinf("\'", (*tmp), 2), "\'", 1): 0;
	b->mod & PB ? write(1, *tmp, ft_strlen(*tmp)) : 0;
	if (b->mod & TB && (ptr = ft_strchr(*tmp, '/')) && *(ptr + 1))
		(*tmp) = ft_strdups(ptr + 1, tmp);
	if (b->mod & EB && (ptr = ft_strchr(*tmp, '.')))
		(*tmp) = ft_strdups(ptr, tmp);
	if (b->mod & XB && (arr = ft_strsplit((*tmp), ' ')))
	{
		ft_strdel(tmp);
		while (arr[++i])
		{
			arr[i] = ft_strjoinf(ft_strjoinf("\'", arr[i], 2), "\'", 1);
			(*tmp) = ft_strjoinf(ft_strjoinf(*tmp, arr[i], 1), " ", 1);
		}
		ft_free(arr, NULL);
	}
}

int      mod_cmd(char **cmd, char **array, t_bang *bang)
{
	int     ret;
	char    *beg;
	char    *end;

	(*cmd)[bang->b] = 0;
	beg = ft_strdup(*cmd);
	end = ft_strdup(*cmd + bang->e);
	ret = -1;
	while (array[++ret])
	if (!ft_strcmp(array[ret], bang->s1))
	{
		array[ret] = ft_strdups(bang->s2, &array[ret]);
		break ;
	}
	if (!array[ret])
		return (fd_printf(2, "\n42sh: substituion failed\n"));
	ft_strdel(cmd);
	ret = -1;
	beg ? (*cmd) = ft_strdup(beg) : 0;
	while (array[++ret])
	(*cmd) = ft_strjoinf(ft_strjoinf(*cmd, array[ret], 0), " ", 1);
	(*cmd) = ft_strjoinf((*cmd), end, 3);
	return (2);
}

static int  last_bang(char **cmd, char **buf)
{
	ft_strdel(cmd);
	*cmd = ft_strdupf(buf);
	return (1);
}

int 		fill_buf(char *tmp, char **cmd, int i, int j)
{
	static char		*buf = NULL;
	char			*sub;
	int				b;
	int				e;

	!buf ? buf = ft_strdup(*cmd) : 0;
	if (j)
    	return (last_bang(cmd, &buf));
	while (buf[++i])
		if (buf[i] == '!')
		{
			b = i ;
			buf[i + 1] == '!' ? i += 1 : 0;
			while (buf[++i] && buf[i] != '<' && buf[i] != '>' && buf[i] != '\"'
			&& buf [i] != '\'' && buf[i] != ';' && buf[i] != '|' &&
			buf[i] != '&' && buf[i] != '!')
        		;
			e = i;
			sub = ft_strdup(buf + e);
			buf[b] = 0;
			buf = ft_strjoinf(ft_strjoinf(buf, tmp, 1), sub, 3);
			break ;
		}
	return (0);
}
