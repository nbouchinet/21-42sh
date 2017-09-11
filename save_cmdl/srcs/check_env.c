/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/10 15:51:15 by hpelat            #+#    #+#             */
/*   Updated: 2017/06/10 15:51:17 by hpelat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void		add_missing_var(char **env, char **newenv, int vif)
{
	int		k;
	char	tmp[512];

	getcwd(tmp, 512);
	k = ft_tablen(env) - 1;
	if (!(vif & 1))
		newenv[++k] = ft_strdup(
		"PATH=/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/usr/local/munki");
	if (!(vif & 2))
		newenv[++k] = ft_strdup("TERM=xterm-256color");
	if (!(vif & 4))
		newenv[++k] = ft_strjoin("PWD=", tmp);
	if (!(vif & 8))
		newenv[++k] = ft_strjoin("OLDPWD=", tmp);
	if (!(vif & 16))
		newenv[++k] = ft_strdup("SHLVL=0");
	newenv[++k] = NULL;
}

char			**check_env(char **env)
{
	int		i;
	int		k;
	int		vif;
	char	tmp[512];
	char	**newenv;

	i = -1;
	if (!(newenv = (char**)malloc(sizeof(char*) * (ft_tablen(env) + 6))))
		exit(fd_printf(2, "malloc error\n"));
	while (env[++i] && (k = -1))
	{
		while (env[i][++k] != '=')
			tmp[k] = env[i][k];
		tmp[k] = 0;
		vif = (!ft_strcmp("PATH", tmp) ? vif | 1 : vif);
		vif = (!ft_strcmp("TERM", tmp) ? vif | 2 : vif);
		vif = (!ft_strcmp("PWD", tmp) ? vif | 4 : vif);
		vif = (!ft_strcmp("OLDPWD", tmp) ? vif | 8 : vif);
		vif = (!ft_strcmp("SHLVL", tmp) ? vif | 16 : vif);
		getcwd(tmp, 512);
		newenv[i] = (!ft_strcmp("SHELL", tmp) ? ft_strjoinf("SHELL=",
		ft_strjoin(tmp, "42sh"), 2) : ft_strdup(env[i]));
	}
	add_missing_var(env, newenv, vif);
	return (newenv);
}
