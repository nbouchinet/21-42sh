/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/24 11:15:17 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/11 10:48:28 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

char	*ft_strat(char **env, int i)
{
	int		k;
	char	*home;

	k = 0;
	home = NULL;
	if (!env)
		return ("");
	while (env[k] &&
	((home = ft_strstr(env[k], i == 1 ? "HOME" : "OLDPWD")) == NULL))
		k++;
	if (!home)
		return ("");
	else
		return (ft_strchr(home, '/'));
}
