/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_fin5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 02:43:03 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/02 02:44:49 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*create_path(char *env, char *cmd)
{
	int		i;
	char	*str;

	i = ft_strlen(env) + ft_strlen(cmd);
	if (!(str = (char*)malloc(sizeof(char) * (i + 2))))
		return (NULL);
	ft_bzero(str, i + 2);
	ft_strcat(str, env);
	i = ft_strlen(env);
	if (env[i - 1] != '/')
		ft_strcat(str, "/");
	ft_strcat(str, cmd);
	return (str);
}

char	*get_dir(char *cmd)
{
	int		i;
	int		index;
	char	*ncmd;

	i = -1;
	while (cmd[++i])
		if (cmd[i] == '/')
			index = i;
	i = -1;
	if (!(ncmd = ft_strnew(index + 1)))
		return (NULL);
	while (++i <= index)
		ncmd[i] = cmd[i];
	return (ncmd);
}

void		stock_restore(int mod)
{
	static int		stdin = -1;
	static int		stdout = -1;
	static int		stderr = -1;

	if (mod)
	{
		stdin = dup(STDIN_FILENO);
		stdout = dup(STDOUT_FILENO);
		stderr = dup(STDERR_FILENO);
	}
	else
	{
		dup2(stdin, STDIN_FILENO);
		dup2(stdout, STDOUT_FILENO);
		dup2(stderr, STDERR_FILENO);
		close(stdin);
		close(stdout);
		close(stderr);
	}
}
