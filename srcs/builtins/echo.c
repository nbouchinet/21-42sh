/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpelat <hpelat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/05 15:35:31 by hpelat            #+#    #+#             */
/*   Updated: 2017/09/28 18:10:42 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static char		*joinvar(char *arg, t_env **env)
{
	int		i;
	char	*tmp;
	t_env	*save;

	i = -1;
	save = *env;
	tmp = (char*)malloc(sizeof(char) * (ft_strlen(arg) + 1));
	while (arg[++i] && arg[i] != '$' && arg[i] != '=')
		tmp[i] = arg[i];
	tmp[i] = 0;
	while (save->next && ft_strcmp(save->var, tmp))
		save = save->next;
	free(tmp);
	if (!ft_strcmp(save->var, tmp))
		return (ft_strjoin(save->value, arg + i));
	while (arg[i] && arg[i] != '$' && arg[i] != '=')
		i += 1;
	return (ft_strdup((arg[i] ? arg + i : "")));
}

static void		if_env(char **arg, t_env **env)
{
	int		i;
	char	*tmp;
	char	*save;

	i = -1;
	while ((*arg)[++i])
	{
		if ((*arg)[i] == '$')
		{
			tmp = joinvar((*arg) + i + 1, env);
			save = (*arg);
			(*arg)[i] = 0;
			(*arg) = ft_strjoin((*arg), tmp);
			free(tmp);
			free(save);
			i -= 1;
		}
	}
	i = -1;
	if (!(*arg)[0])
	{
		free(arg[0]);
		while (arg[++i])
			arg[i] = arg[i + 1];
	}
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
int				ft_echo(t_ast **ast, t_env **env)
{
	int		i;
	char	**arg;

	(*ast)->right ? io_seq(&(*ast)->right->right) : 0;
	if (!(arg = creat_arg_env(&(*ast)->left->right)) || !arg[0])
		return (write(1, "\n", 1));
	i = (arg[0] && !ft_strcmp(arg[0], "-n") ? 1 : 0);
	while (arg[i])
	{
		if_env(arg + i, env);
		if (write(1, arg[i], ft_strlen(arg[i])) && arg[++i])
			write(1, " ", 1);
	}
	if (arg && arg[0] && !ft_strcmp(arg[0], "-n"))
	{
		if (arg[1])
		{
			tputs(tgetstr("mr", NULL), 1, ft_putchar);
			write(1, "%\n", 2);
			tputs(tgetstr("me", NULL), 1, ft_putchar);
		}
	}
	else
		ft_putendl("");
	ft_free(arg, NULL, 1);
	return (1);
}
