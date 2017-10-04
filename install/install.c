/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   install.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 17:44:44 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/04 18:54:40 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"
#define RE 1
#define MAKE 2
#define CLEAN 4
#define FCLEAN 8
#define OBJ 16

int		check_opt(char **av)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (av[++i])
	{
		if (!strcmp(av[i], "-m"))
			return (MAKE);
		else if (!strcmp(av[i], "-r"))
			return (RE);
		else if (!strcmp(av[i], "-c"))
			return (CLEAN);
		else if (!strcmp(av[i], "-f"))
			return (FCLEAN);
		else if (!strcmp(av[i], "-o"))
			return (OBJ);
	}
	return (0);
}

void	recup_make(void)
{
	int		fd[2];
	char	*str;
	pid_t	son;

	if (!pipe(fd))
	{
		if (!(son = fork()))
		{
			ft_putendl("pass");
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			while (get_next_line(fd[0], &str))
			{
				ft_putendl_fd(str, 2);
				ft_putendl_fd("========", 2);
				ft_strdel(&str);
			}
		}
		wait(NULL);
	}
}
int		main(int ac, char **av)
{
	int		i;
	if ((i = check_opt(av)))
	{
		if (i & MAKE)
			recup_make();
		// else if (i & RE)
		// else if (i & CLEAN)
		// else if (i & FCLEAN)
	}
	return (500);
}
