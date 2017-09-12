/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 14:59:44 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/12 09:35:04 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void remalloc_cmdl(t_line *line, int len)
{
	char	*tmp;

	tmp = line->str;
	if (!(line->str = (char *)malloc(sizeof(char) * (len + 1024))))
		exit(0);
	ft_memset(line->str, 0, (len + 1024));
	line->str = ft_strcpy(line->str, tmp);
	free(tmp);
	line->len += 1024;
}

static int	regular_print(t_line *line, char buf[], int i)
{
	int		len;
	int		j;

	len = ft_strlen(line->str);
	if (len + line->pr >= line->co * line->li - (line->co + 1))
	{
		beep();
		return (-1);
	}
	len == line->len ? remalloc_cmdl(line, len) : 0;
	if (line->str[i] == 0)
		line->str = ft_strcat(line->str, buf);
	else
	{
		j = len;
		while (j-- > i)
			line->str[j + 1] = line->str[j];
		line->str[i] = buf[0];
	}
	write(1, line->str + i, ft_strlen(line->str + i));
	line->cur += ft_strlen(line->str + i);
	!(line->cur % line->co) ? tputs(tgetstr("do", NULL), 1, ft_putchar) : 0;
	i += (len = (int)ft_strlen(line->str) - len) > 1 ? len : 0;
	return (i);
}

int 		print(t_cmdl *cmdl, char buf[])
{
	int		i;

	if (!(PRINT(buf)) && !(SH(buf)))
		return (1);
	if (PRINT(buf) && !(cmdl->opt & CHIS_S))
	{
		i = regular_print(&cmdl->line, buf, cmdl->line.cur - cmdl->line.pr);
		if (i >= 0)
		{
			cmdl->ccp.start += cmdl->ccp.start == -1 ? 0 : 1;
			while (cmdl->line.cur - cmdl->line.pr - 1 > i)
				arrow_left(cmdl);
		}
	}
	else
		search_history_print(cmdl, buf);
	return (1);
}
