/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: khabbar <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 09:32:04 by khabbar           #+#    #+#             */
/*   Updated: 2017/04/05 20:50:40 by khabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libftprintf.h"

static int check_str(t_gnl *current_fd, char **line)
{
	char *endl;
	char *tmp;

	if (!(endl = ft_strchr(current_fd->str, '\n')))
		return (0);
	*endl = '\0';
	*line = ft_strdup(current_fd->str);
	if (*(endl + 1) != '\0')
	{
		tmp = current_fd->str;
		current_fd->str = ft_strdup(current_fd->str
				+ ((endl + 1) - current_fd->str));
		free(tmp);
	}
	else
	{
		free(current_fd->str);
		current_fd->str = NULL;
	}
	return (1);
}

static int check_read(t_gnl *current_fd, char *buff, char **line)
{
	char *endl;

	if (!(endl = ft_strchr(buff, '\n')))
		return (0);
	if (current_fd->str)
	{
		*endl = '\0';
		*line = ft_strjoin(current_fd->str, buff);
		free(current_fd->str);
		current_fd->str = NULL;
		if (*(endl + 1) != '\0')
			current_fd->str = ft_strdup(buff + ((endl + 1) - buff));
		return (1);
	}
	if (!current_fd->str)
	{
		*endl = '\0';
		*line = ft_strdup(buff);
		if (*(endl + 1) != '\0')
			current_fd->str = ft_strdup(buff + ((endl + 1) - buff));
		return (1);
	}
	return (1);
}

static t_gnl *find_fd(t_gnl *current_fd, int fd)
{
	t_gnl*tmp;

	tmp = current_fd;
	if (tmp)
	{
		while (tmp->next)
		{
			if (tmp->fd == fd)
				return (tmp);
			tmp = tmp->next;
		}
		if (tmp->fd == fd)
			return (tmp);
		if (!(tmp->next = (t_gnl*)malloc(sizeof(struct s_gnl))))
			return (NULL);
		tmp = tmp->next;
	}
	else if (!(tmp = (t_gnl*)malloc(sizeof(struct s_gnl))))
		return (NULL);
	tmp->fd = fd;
	tmp->str = NULL;
	tmp->next = NULL;
	return (tmp);
}

static int loop(int rd, t_gnl *current_fd, char *buff, char **line)
{
	char *tmp;

	buff[rd] = '\0';
	if (check_read(current_fd, buff, line) == 1)
		return (1);
	if (current_fd->str)
	{
		tmp = current_fd->str;
		current_fd->str = ft_strjoin(current_fd->str, buff);
		free(tmp);
	}
	else
		current_fd->str = ft_strdup(buff);
	ft_strclr(buff);
	return (0);
}

int get_next_line(const int fd, char **line)
{
	static t_gnl *head = NULL;
	t_gnl *current_fd;
	char buff[BUFF_SIZE + 1];
	int rd;

	current_fd = find_fd(head, fd);
	if (!head)
		head = current_fd;
	if (current_fd->str != NULL && check_str(current_fd, line) == 1)
		return (1);
	while ((rd = read(current_fd->fd, buff, BUFF_SIZE)) > 0)
		if (loop(rd, current_fd, buff, line) == 1 || rd == -1)
			return (rd == -1 ? -1 : 1);
	if (current_fd->str == NULL)
		return (rd);
	if (current_fd->str != NULL)
	{
		*line = ft_strdup(current_fd->str);
		free(current_fd->str);
		current_fd->str = NULL;
		return (1);
	}
	return (0);
}
