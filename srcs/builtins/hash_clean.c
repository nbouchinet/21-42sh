/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_clean.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 15:27:47 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/10 20:27:05 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		clean_hash(t_ast *ast, t_job **job, t_hash **table)
{
	(void)ast;
	(void)job;
	return (clear_table(table));
}

int		hash_cmd(char *cmd)
{
	int		i;
	int		key;

	i = -1;
	key = 0;
	while (cmd[++i])
		key += cmd[i];
	return (key);
}
