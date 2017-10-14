/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion_func2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 15:19:53 by khabbar           #+#    #+#             */
/*   Updated: 2017/10/14 15:20:01 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int	count_metha_char(char **src)
{
	char	*ptr;
	int		metha_char;

	ptr = *src;
	metha_char = 0;
	while (*ptr)
	{
		if (*ptr == ' ' || *ptr == '<' || *ptr == '>' || *ptr == '|' ||
		*ptr == '&' || *ptr == '\\' || *ptr == ';' || *ptr == '\"' ||
		*ptr == '\'')
			metha_char++;
		ptr++;
	}
	return (metha_char);
}

void 		escape_metha(char **src)
{
	char	*head;
	char	*str;
	char	*ptr;

	if (!(str = ft_memalloc(ft_strlen(*src) + count_metha_char(src) + 1)))
		exit (EXIT_FAILURE);
	head = str;
	ptr = *src;
	while (*ptr)
	{
		if (*ptr == ' ' || *ptr == '<' || *ptr == '>' || *ptr == '|' ||
		*ptr == '&' || *ptr == '\\' || *ptr == ';' || *ptr == '\"' ||
		*ptr == '\'')
		{
			*str = '\\';
			str++;
		}
		*str = *ptr;
		str++;
		ptr++;
	}
	*str = 0;
	*src = head;
}
