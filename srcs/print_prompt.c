/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_promt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/05 13:16:09 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/12 17:27:58 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

/*
**	A supprimer
*/

t_env			*lst_at(t_env **env, char *cmp)
{
	t_env	*tmp;

	tmp = *env;
	if (!tmp)
		return (NULL);
	while (tmp->next && ft_strcmp(tmp->var, cmp))
		tmp = tmp->next;
	return (tmp);
}

void			print_prompt(void)
{
	t_cmdl	*cmdl;
	char	buff[1024];

	cmdl = *cmdl_slg();
	if (cmdl->lstenv)
		ft_printf("%@42sh: %s%@",
		H_BLUE, lst_at(&(cmdl)->lstenv, "PWD")->value, I);
	else
	{
		getcwd(buff, 1024);
		ft_printf("%@42sh: %s\n%@", H_YELLOW, buff, I);
	}
	if (!(cmdl->opt & CSQ) && !(cmdl->opt & CDQ))
		write(1, "\n$> ", 4);
	else if ((cmdl->opt & CSQ) || (cmdl->opt & CDQ))
		cmdl->opt & CSQ ? write(1, "\nquote> ", 8)
		: write(1, "\ndquote> ", 9);
}
