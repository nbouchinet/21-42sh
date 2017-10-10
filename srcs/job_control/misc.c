/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 00:33:04 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/10 22:17:03 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		check_equal(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == '=')
			return (1);
	return (0);
}

int		test(char *s)
{
	if (check_equal(s) == 1)
		return (1);
	return (0);
}

int		find_fd(int fd, t_fd **lst)
{
	t_fd	*tmp;

	if (*lst)
	{
		tmp = *lst;
		while (tmp && tmp->fd != fd)
			tmp = tmp->next;
		if (!tmp)
			return (0);
	}
	return (1);

}

void	close_fd(t_fd **lst)
{
	t_fd	*tmp;
	t_fd	*node;

	if (*lst)
	{
		tmp = *lst;
		while (tmp)
		{
			node = tmp;
			close(node->fd);
			node->fd = 0;
			tmp = tmp->next;
			free(node);
		}
		*lst = NULL;
	}
}
void	close_rdir(int fd, int mod)
{
	t_fd		*tmp;
	t_fd		*node;
	static t_fd	*lst = NULL;

	if (mod)
	{
		if (!find_fd(fd, &lst))
		{
			if (!(node = (t_fd*)malloc(sizeof(t_fd))))
				return ;
			node->next= NULL;
			if (lst)
			{
				tmp = lst;
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = node;
			}
			else
				lst = node;
		}
	}
	else
		close_fd(&lst);
}
