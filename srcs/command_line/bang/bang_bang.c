/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_bang.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 18:20:41 by khabbar           #+#    #+#             */
/*   Updated: 2017/07/08 18:20:52 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int    get_modifiers(char *arr, t_bang *bang)
{
	arr[0] == 'h' ? bang->mod |= HB : 0;
	arr[0] == 't' ? bang->mod |= TB : 0;
	arr[0] == 'r' ? bang->mod |= RB : 0;
	arr[0] == 'e' ? bang->mod |= EB : 0;
	arr[0] == 'p' ? bang->mod |= PB : 0;
	arr[0] == 'q' ? bang->mod |= QB : 0;
	arr[0] == 'x' ? bang->mod |= XB : 0;
	if (!ft_strchr("htrepqx", arr[0]))
		return (fd_printf(2, "\n42sh: %c: unrecognized history modifier",\
		arr[0]));
	return (0);
}

static int    get_designators(char *arr, t_bang *bang)
{
	char	**sub;

    if (arr[0] >= '0' && arr[0] <= '9' && !ft_strchr(arr, '-') &&
    !ft_strchr(arr, '*'))
		bang->des = ft_atoi(arr);
    else if (arr[0] == '^')
		bang->des = 1;
    else if (arr[0] == '$')
		bang->des = -1;
    else if (ft_strchr(arr, '-'))
    {
		sub = ft_strsplit(arr, '-');
		bang->x = ft_atoi(sub[0]);
		bang->y = sub[1] ? ft_atoi(sub[1]) : -2;
		ft_free(sub, NULL);
	}
    else if (ft_strchr(arr, '*'))
    {
		bang->x = arr[0] == '*' ? 1 : ft_atoi(arr);
		bang->y = -1;
    }
    else
		return (fd_printf(2, "\n42sh: !%s: event not found", arr));
    return (0);
}

static int    get_event(char *arr, t_bang *bang, t_his *his)
{
	char      **sub;

    if (arr[0] >= '0' && arr[0] <= '9')
		bang->n = ft_atoi(arr) - 1;
    else if (arr[0] == '-' && arr[1] && arr[1] >= '0' && arr[1] <= '9')
		bang->n = (ft_atoi(arr + 1) - 1) * -1;
    else if (arr[0] == '!')
		bang->n = 0;
	else if (arr[0] == '?')
		bang->string = arr + 1;
    else if (arr[0] == '^')
    {
		sub = ft_strsplit(arr, '^');
		bang->s1 = ft_strdup(sub[0]);
		bang->s2 = ft_strdup(sub[1]);
		ft_free(sub, NULL);
	}
    else if (ft_isalpha(arr[0]))
		bang->string = arr;
    else
		return (fd_printf(2, "\n42sh: !%s: event not found", arr));
    if (bang->n && (bang->n < 0 ? -bang->n : bang->n) > lst_len(his))
		return (fd_printf(2, "\n42sh: !%d: no such event", bang->n));
	return (0);
}

static int    his_error(char *str)
{
	fd_printf(2, "\n42sh: %c%c: event not found", str[0] ==  '^' ?
	'!' : str[0], str[0] == '^' ? '!' : str[1]);
	ft_free(NULL, &str);
	return (1);
}

int           bang_bang(char **cmd, char *str, t_bang *bang, int len)
{
  t_his		*his;
  char		**array;

	str[0] == ':' ? str = ft_strjoinf("!", str, 2) : 0;
	his = win_sgt()->his;
	if (!his->prev)
		return (his_error(str));
	while (his->prev)
  		his = his->prev;
	array = ft_strsplit(str, ':');
	len = ft_tablen(array);
	if (0 < len && get_event(array[0], bang, his))
		return (ft_free(array, &str));
	if (1 < len && ((array[1][0] >= '0' && array[1][0] <= '9') ||
		array[1][0] == '^' || array[1][0] == '$') &&
		get_designators(array[1], bang))
    return (ft_free(array, &str));
	if ((2 < len && ft_isalpha(array[2][0]) && get_modifiers(array[2], bang)) ||
  	(1 < len && ft_isalpha(array[1][0]) && get_modifiers(array[1], bang)))
		return (ft_free(array, &str));
	if ((len = do_sub(his, bang, cmd, array[0])))
		return (len == 2 ? ft_free(array, &str) + 1 : ft_free(array, &str));
	ft_free(array, &str);
	return (bang->mod & PB ? 1 : 0);
}
