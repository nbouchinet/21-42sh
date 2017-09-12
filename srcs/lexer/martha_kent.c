/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   martha_kent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/04 19:08:51 by zadrien           #+#    #+#             */
/*   Updated: 2017/05/24 13:46:53 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		count_tab(char **ta)
{
	int		i;

	i = 0;
	while (ta[i])
		i++;
	return (i);
}

int		arg_check(int ac, int i, char **av, char **envp)
{
	if (ac != i)
	{
		ft_errormsg("usage: ", NULL, "./21sh");
		return (0);
	}
	if (count_tab(envp) == 0)
	{
		ft_errormsg("21sh: ", NULL, "env not found.");
		return (0);
	}
	if (!av)
	{
		ft_errormsg("argv: ", NULL, "Impossible error");
		return (0);
	}
	return (1);
}

int		io_number(char *str)
{
	int		i;
	int		j;

	if ((i = ft_strlen(str)) == 1)
	{
		if ((j = ft_atoi(str)) > 0 && j < 9)
			return (1);
	}
	return (0);
}

int		is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v')
		return (1);
	return (0);
}

int		check_end(char *line)
{
	int		i;

	i = 0;
	while (line[i] && is_space(line[i]) == 1)
		i++;
	if (!line[i])
		return (0);
	return (1);
}
