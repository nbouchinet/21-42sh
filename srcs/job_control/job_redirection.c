/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_redirection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 11:45:17 by zadrien           #+#    #+#             */
/*   Updated: 2017/09/27 11:51:47 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int		*stock_restore(int fd, int mod)
{
	static const int		fd[10] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

	if (mod)
	{
		
	}
}

int		rdir_builtin(t_ast **ast)
{
	t_ast **
}

int		redir_builtin(t_ast **ast)
{
	int						i;
	t_ast					*tmp;
	static const t_rdir		rdir[6] = {{RDIR, &wtf_rdir}, {RRDIR, &wtf_rdir},
		{AGRE, &agre}, {BDIR, &bdir}, {BBDIR, &bbdir}, {BGRE, &bgre}};

		i = -1;
	tmp = *ast;
	if (tmp && (tmp->type >= RDIR && tmp->type <= BGRE))
		if (tmp->right)
			if (redir_builtin(&tmp->right))
				while (++i < 6)
					if (tmp->type == rdir[i].t)
						if (rdir[i].f(&tmp))
							return (1);
	return (0);
}
