/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 15:08:22 by zadrien           #+#    #+#             */
/*   Updated: 2017/10/22 14:13:23 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int		check_local_name(t_ast *tmp, int *len)
{
	*len = 1;
	while (tmp)
	{
		if (!ft_isalpha(tmp->str[0]))
		{
			fd_printf(2, "21sh: %s: not a valid identifier\n", tmp->str);
			return (-1);
		}
		(*len)++;
		tmp = tmp->right;
	}
	return (*len);
}

static int		get_local(t_ast **ast, t_read *var)
{
	t_ast		*tmp;
	t_ast		*prev;
	int			i;
	int			len;

	tmp = *ast;
	i = -1;
	if (check_local_name(tmp, &len) == -1)
		return (1);
	if (!(var->local = (char **)malloc(sizeof(char *) * len)))
		exit(EXIT_FAILURE);
	var->local[len - 1] = NULL;
	while (tmp)
	{
		var->local[++i] = ft_strjoin(tmp->str, "=");
		prev = tmp;
		tmp = tmp->right;
	}
	*ast = prev;
	return (0);
}

static int		options(t_ast **tmp, t_read *var, int *ret)
{
	static const t_opt	opt[7] = {{"d", &delim}, {"n", &nchars},
	{"p", &prompt}, {"r", &back_slash}, {"s", &silent}, {"t", &rtimeout},
	{"u", &fd}};
	char				*str;
	int					i;

	str = (*tmp)->str + 1;
	i = -1;
	while (*str)
	{
		while (++i < 7)
			if (opt[i].c[0] == *str && opt[i].f(var, tmp, str + 1))
				return (1);
		if (!ft_strchr("dnprstu", *str))
		{
			fd_printf(2, "21sh: read: -%c: invalid option\n%s%s\n",
			*str, RU1, RU2);
			return (1);
		}
		str++;
	}
	*ret = 1;
	return (0);
}

static int		parse_opt(t_ast **ast, t_read *var)
{
	t_ast		*tmp;
	int			ret;

	tmp = *ast;
	while (tmp)
	{
		ret = 0;
		if (tmp->str[0] == '-' && ((tmp->str[1] == '-' && !tmp->str[2]) ||
		!tmp->str[1]))
			return (0);
		if (tmp->str[0] == '-' && options(&tmp, var, &ret))
			return (1);
		if (!ret && tmp->str[0] != '-' && get_local(&tmp, var))
			return (1);
		tmp = tmp->right;
	}
	return (0);
}

int				ft_read(t_ast **ast, t_env **env)
{
	t_read		var;
	t_cmdl		*cmdl;
	char		buf[6];

	(void)env;
	cmdl = *cmdl_slg();
	ft_memset(&var, 0, sizeof(t_read));
	if ((*ast)->left->right && parse_opt(&(*ast)->left->right, &var))
		return (0);
	if (!var.local)
	{
		if (!(var.local = (char**)malloc(sizeof(char*) * 2)))
			exit(EXIT_FAILURE);
		var.local[0] = ft_strdup("REPLY=");
		var.local[1] = NULL;
	}
	mode_on(*cmdl_slg());
	cmdl->term.c_lflag &= ~ECHO;
	if (tcsetattr(1, TCSADRAIN, &cmdl->term) == -1)
		return (fd_printf(2, "unset_shell: tcsetattr: ERROR\n"));
	read_input(&var, ft_memalloc(512), buf);
	mode_off(*cmdl_slg());
	var.local ? ft_freetab(var.local) : 0;
	var.delim ? ft_strdel(&var.delim) : 0;
	return (1);
}
