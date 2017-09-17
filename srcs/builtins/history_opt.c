/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_opt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 12:26:29 by khabbar           #+#    #+#             */
/*   Updated: 2017/09/12 10:30:01 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void no_options(t_his **his, int offset, int his_len)
{
	(void)his;
	(void)offset;
	(void)his_len;
}

static void hist_clear(t_his **his, int offset, int his_len)
{
	(void)offset;
	(void)his_len;
	his_del(his, 1);
}

void 		run_his(t_his **his, int opt, int offset, int his_len)
{
	int		i;
	static const	t_hist	option[1] = {{1, &hist_clear}/*, {2 , &hist_del},
	{4, &hist_append}, {8, &hist_read}, {16, &hist_read}, {32, &hist_append},
	{128, &hist_sarg}*/};

	i = -1;
	if (!opt)
		no_options(his, offset, his_len);
	else
		while (++i < 1)
			if (opt & option[i].op)
				option[i].f(his, offset, his_len);
}
