/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 15:23:17 by khabbar           #+#    #+#             */
/*   Updated: 2017/05/29 15:23:20 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

typedef struct        s_ls
{
    char            padx[36];
    char            *name;
    struct s_ls		*next;
}                    t_ls;

static int 		is_first_word(char *cmd, int i)
{
	while (--i && cmd[i] == ' ')
		;
	if (cmd[i] == ';' || i == 0 || cmd[i] == '|' ||
	(cmd[i] == '&' && i > 0 && cmd[i - 1] == '&'))
		return (1);
	return (0);
}

static char     *ft_get_env_var(char **big, char *little)
{
		size_t  i;

		i = -1;
		if (!big)
				return (NULL);
		while (big[++i])
			if (ft_strenv(big[i], little))
				return (big[i] + ft_strlen(little) + 1);
		return (NULL);
}

static void		insert(t_ls **head, t_ls *link, int i)
{
	t_ls		*tmp;
	t_ls		*save;

	tmp = *head;
	if (i == 0)
	{
		link->next = tmp;
		*head = link;
	}
	else
	{
		while (i-- > 1)
			tmp = tmp->next;
		save = tmp->next;
		tmp->next = link;
		link->next = save;
	}
}

t_ls			*fill_lst(t_ls **head, char *name, char *comp, int param)
{
	t_ls		*tmp;
	t_ls		*stock;
	int			i;

	i = 0;
	if (!(tmp = (t_ls *)malloc(sizeof(t_ls))))
		exit(fd_printf(2, "malloc error\n"));
	tmp->name = (param == 2 && !ft_strcmp(comp, name) ? ft_strjoin(name, "/") : ft_strdup(name));
	tmp->next = NULL;
	if (!(*head))
		return (tmp);
	else
	{
		stock = *head;
		while (stock && ft_strcmp(stock->name, name) < 0)
		{
			i++;
			stock = stock->next;
		}
		insert(head, tmp, i);
		return (tmp);
	}
}

static t_ls        *ft_putpaddx(t_ls *ls, int maxlen)
{
    int			i;
    int			save;
    t_ls		*tmp;

    tmp = ls;
    while (tmp)
    {
        i = 0;
        save = ft_strlen(tmp->name);
        while (i < maxlen - save)
        {
            tmp->padx[i] = ' ';
            i += 1;
        }
        tmp->padx[i] = 0;
        tmp = tmp->next;
    }
    return (ls);
}

t_ls            *ft_padd_x(t_ls *ls, int *maxlen)
{
    t_ls    *tmp;
    int     save;

    tmp = ls;
    (*maxlen) = 0;
    if (tmp)
    {
        while (tmp)
        {
            save = ft_strlen(tmp->name);
            if (save > (*maxlen))
                (*maxlen) = save;
            tmp = tmp->next;
        }
    }
    (*maxlen) += 5;
    return (ft_putpaddx(ls, (*maxlen)));
}

void				print_lst(t_ls **head, t_win **win, char *cmd)
{
	int				len;
	unsigned long	winsize;
	t_ls			*tmp;

	tmp = (*head);
	ft_padd_x(*head, &len);
	winsize = (*win)->co - len - 5;
	len = 0;
	while (tmp)
	{
		len += ft_printf("%s", tmp->name);
		if ((len + ft_strlen(tmp->padx) < winsize))
			len += ft_printf("%s", tmp->padx);
		else
			tmp->next ? ft_printf("%n\n", &len) : 0;
		tmp = tmp->next;
	}
	write(1, "\n", 1);
	print_prompt();
	write(1, cmd, ft_strlen(cmd));
}

static int 		list_len(t_ls **list)
{
	int			len;
	t_ls		*tmp;

	len = 0;
	tmp = *list;
	if (tmp)
	{
		len = 1;
		while (tmp->next)
		{
			len += 1;
			tmp = tmp->next;
		}
		return (len);
	}
	return (0);
}

int 			list_exe(char *tmp, char **path, t_win **win, char **cmd)
{
	struct dirent	*rdd;
	DIR				*dir;
	t_ls			*list;
	char			buf[3] = {27, 91, 70};
	char			*save;
	int				i;

	list = NULL;
	i = -1;
	while (path[++i])
	{
		dir = opendir(path[i]);
		while ((rdd = readdir(dir)) != 0)
		{
			if (ft_strncmp(rdd->d_name, tmp, ft_strlen(tmp)) == 0)
				!list ? list = fill_lst(&list, rdd->d_name, tmp, 1) :
				fill_lst(&list, rdd->d_name, tmp, 1);
		}
		closedir(dir);
	}
	if (list && list_len(&list) > 1)
	{
		arrows((*win), (*cmd), buf);
		write(1, "\n", 1);
		print_lst(&list, win, (*cmd));
		return (1);
	}
	else if (list)
	{
		save = ft_strsub((*cmd), (*win)->cur - (*win)->pr,
		ft_strlen((*cmd)) - (*win)->cur - (*win)->pr);
		while ((*cmd)[(*win)->cur - (*win)->pr] != ' ' && (*cmd)[(*win)->cur - (*win)->pr] != '|'
		&& (*cmd)[(*win)->cur - (*win)->pr] != ';' && (*cmd)[(*win)->cur - (*win)->pr] != '&' &&
		(*cmd)[(*win)->cur - (*win)->pr] != '<' && (*cmd)[(*win)->cur - (*win)->pr] != '>'
		&& (*win)->cur - (*win)->pr)
			arrow_left(*win);
		(*cmd)[(*win)->cur - (*win)->pr + ((*win)->cur - (*win)->pr ? 1 : 0)] = 0;
		(*cmd) = ft_strjoinf((*cmd), (list)->name, 1);
		while ((*win)->cur > (*win)->pr)
			arrow_left(*win);
		write(1, (*cmd), ft_strlen((*cmd)));
		(*win)->cur += ft_strlen((*cmd));
		return (1);
	}
	return (0);
}

char			*get_path(char **str)
{
	char		*path;
	char		*temp;
	int			i;
	int			save;

	save = 0;
	i = -1;
	while ((*str)[++i])
		if ((*str)[i] == '/')
			save = i;
	if ((*str)[save] == '/')
	{
		temp = (*str);
		path = ft_strsub((*str), 0, save + 1);
		(*str) = ft_strsub((*str), save + 1, ft_strlen((*str) + save));
		free(temp);
	}
	else
		path = ft_strdup(".");
	return (path);
}

void			list_files(char *tmp, t_win **win, char **cmd)
{
	struct dirent	*rdd;
	DIR				*dir;
	t_ls			*list;
	char			buf[3] = {27, 91, 70};
	char			*save;
	char			*path;

	list = NULL;
	path = get_path(&tmp);
	if (!(dir = opendir(path)))
		exit (fd_printf(2, "error\n"));
	while ((rdd = readdir(dir)) != 0)
	{
		if (ft_strncmp(rdd->d_name, tmp, ft_strlen(tmp)) == 0)
			!list ? list = fill_lst(&list, rdd->d_name, tmp, 2) :
			fill_lst(&list, rdd->d_name, tmp, 2);
	}
	closedir(dir);
	if (list && list_len(&list) > 1)
	{
		arrows((*win), (*cmd), buf);
		write(1, "\n", 1);
		print_lst(&list, win, (*cmd));
	}
	else if (list)
	{
		save = ft_strsub((*cmd), (*win)->cur - (*win)->pr,
		ft_strlen((*cmd)) - (*win)->cur - (*win)->pr);
		while ((*cmd)[(*win)->cur - (*win)->pr] != ' ' && (*cmd)[(*win)->cur - (*win)->pr] != '|'
		&& (*cmd)[(*win)->cur - (*win)->pr] != ';' && (*cmd)[(*win)->cur - (*win)->pr] != '&' &&
		(*cmd)[(*win)->cur - (*win)->pr] != '<' && (*cmd)[(*win)->cur - (*win)->pr] != '>'
		&& (*win)->cur - (*win)->pr > 0)
			arrow_left(*win);
		(*cmd)[(*win)->cur - (*win)->pr + ((*win)->cur - (*win)->pr ? 1 : 0)] = 0;
		path[0] != '.' ? (*cmd) = ft_strjoinf((*cmd), ft_strdup(path) , 1) : 0;
		(*cmd) = ft_strjoinf((*cmd), (list)->name, 1);
		while ((*win)->cur > (*win)->pr)
			arrow_left(*win);
		write(1, (*cmd), ft_strlen((*cmd)));
		(*win)->cur += ft_strlen((*cmd));
	}
	else
		beep();
	// lst_del();
}

static int		only_space(char *cmd)
{
	int			i;

	if (!cmd)
		return (1);
	i = -1;
	while (cmd[++i])
		if (cmd[i] != ' ' && cmd[i] != 0)
			return (0);
	return (1);
}

void    		completion(t_win **win, char **cmd, char **env)
{
	int     i;
	int     first;
	char    *tmp;
	char	**path;

	if (!(*cmd))
	{
		write(1, "RTFM\n", 5);
		print_prompt();
	}
	if ((!env) || (!ft_get_env_var(env, "PATH")) || only_space((*cmd)))
		return ;
	i = (*win)->cur - (*win)->pr;
	while (--i > 0 && (*cmd)[i] != ' ' && (*cmd)[i] != '|' && (*cmd)[i] != ';'
	&& (*cmd)[i] != '&' && (*cmd)[i] != '<' && (*cmd)[i] != '>')
		;
	while ((*cmd)[(*win)->cur - (*win)->pr] && (*cmd)[(*win)->cur - (*win)->pr] != ' ' &&
	(*cmd)[(*win)->cur - (*win)->pr] != '|' && (*cmd)[(*win)->cur - (*win)->pr] != ';' &&
	(*cmd)[(*win)->cur - (*win)->pr] != '&' && (*cmd)[(*win)->cur - (*win)->pr] != '<'
	&& (*cmd)[(*win)->cur - (*win)->pr] != '>')
		arrow_rigth((*win), (*cmd));
	tmp = ft_strsub((*cmd), (i ? i + 1 : i), (*win)->cur - (*win)->pr - i);
	first = is_first_word((*cmd), i + 1);
	path = ft_strsplit(ft_get_env_var(env, "PATH"), ':');
	if (first)
		list_exe(tmp, path, win, cmd) ? 0 : (list_files(tmp, win, cmd));
	else
		list_files(tmp, win, cmd);
}
