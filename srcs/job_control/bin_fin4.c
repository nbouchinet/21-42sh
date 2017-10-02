/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_fin4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 02:42:10 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/02 02:43:27 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		ft_checkbin(DIR *dir, char *cmd)
{
	struct dirent *dirp;

	while ((dirp = readdir(dir)))
		if (ft_strcmp(dirp->d_name, ".") != 0 &&
			ft_strcmp(dirp->d_name, "..") != 0)
			if (ft_strcmp(dirp->d_name, cmd) == 0)
				return (1);
	return (0);
}

char	*var_value(int i, char *var, char *value)
{
	char *str;

	if (!(str = (char*)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	ft_bzero(str, i + 2);
	ft_strcat(str, var);
	ft_strcat(str, "=");
	value ? ft_strcat(str, value) : 0;
	return (str);
}
