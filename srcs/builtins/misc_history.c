/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 21:14:23 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/20 13:34:01 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	hist_clear(t_his **his, int offset, int his_len, char *arg)
{
	(void)offset;
	(void)his_len;
	(void)arg;
	his_del(his, 1);
}
