/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 15:08:22 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/02 15:08:31 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	inner_loop(t_read *var, char **arg, int *i, const t_opt opt[])
{
	int		j;
	int		k;

	j = 0;
	k = -1;
	while (++k < 8 && arg[(*i)][j])
	{
		j += j == 0 && arg[(*i)][j] == '-' ? 1 : 0;
		if (j == 0 && arg[(*i)][j] != '-' &&
		(var->local = ft_strdup(arg[(*i)])))
			return (0);
		if (arg[(*i)][j] == opt[k].c[0])
		{
			if (opt[k].f(var, arg, i, ++j))
				return (1);
			if (opt[k].c[0] != 's' && opt[k].c[0] != 'r')
				break ;
		}
	}
	if (k == 8)
		return (fd_printf(2, "42sh: read: -%c: invalid option\n%s\n",
		arg[(*i)][j], RU));
	return (-1);
}

static int  get_opt(t_read *var, char **arg, int *i)
{
	int					ret;
	static const  t_opt opt[8] = {{"a", &aname} ,{"d", &delim}, {"n", &nchars},
	{"p", &prompt}, {"r", &back_slash}, {"s", &silent}, {"t", &rtimeout},
	{"u", &fd}};

	while (arg[++(*i)])
	{
		ret = inner_loop(var, arg, i, opt);
		if (ret >= 0)
			return (ret);
	}
	return (0);
}

static int 	free_var(t_cmdl *cmdl, t_read *var, char **targ)
{
	cmdl->opt &= ~RRET;
	ft_free(targ, NULL, 1);
	var->delim ? ft_strdel(&var->delim) : 0;
	var->local ? ft_strdel(&var->local) : 0;
	var->stack ? ft_strdel(&var->stack) : 0;
	(var->eot || var->opt & (DR | TR)) ? write(1, "\n", 1) : 0;
	return (1);
}

int         ft_read(t_ast **ast, t_env **env)
{
	t_read  var;
	t_cmdl	*cmdl;
	char	buf[6];
	char    **targ;
	int     i;

	(void)env;
	(*ast)->right ? io_seq(&(*ast)->right->right) : 0;
	cmdl = *cmdl_slg();
	ft_memset(&var, 0, sizeof(t_read));
	targ = creat_arg_env(&(*ast)->left->right);
	i = -1;
	if (targ && get_opt(&var, targ, &i))
		return (0);
	!var.local ? var.local = ft_strdup("REPLY") : 0;
	mode_on(*cmdl_slg());
	cmdl->term.c_lflag &= ~ECHO;
	if (tcsetattr(1, TCSADRAIN, &cmdl->term) == -1)
		return (fd_printf(2, "unset_shell: tcsetattr: ERROR\n"));
	signal(SIGINT, &handle_c);
	read_input(&var, -1, 0, buf);
	mode_off(*cmdl_slg());
	if (!(cmdl->opt & RRET))
		save_input(&var);
	return (free_var(cmdl, &var, targ));
}
