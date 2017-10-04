/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zadrien <zadrien@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 17:16:30 by zadrien           #+#    #+#             */
/*   Updated: 2017/02/10 10:29:46 by zadrien          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_stockbuf(char *str, char *buf)
{
	int		i;
	char	*tmp;

	tmp = ft_strdup(str);
	free(str);
	i = ft_strlen(tmp);
	if (!(str = (char*)malloc(sizeof(char) * (i + ft_strlen(buf) + 1))))
		return (NULL);
	ft_bzero(str, ft_strlen(tmp) + ft_strlen(buf) + 1);
	str = ft_strcat(str, tmp);
	str = ft_strcat(str, buf);
	free(tmp);
	return (str);
}

int		ft_checknline(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == '\n')
			return (1);
	return (0);
}

char	*ft_strline(char *str)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = -1;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if ((line = ft_strnew(i)) == NULL)
		return (NULL);
	ft_bzero(line, i + 1);
	while (++j < i)
		line[j] = str[j];
	return (line);
}

char	*ft_strrest(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	tmp = ft_strdup(str + i);
	free(str);
	str = ft_strdup(tmp);
	free(tmp);
	return (str);
}

int		get_next_line(int fd, char **line)
{
	static char *str = NULL;
	char		*buf;
	int			ret;

	if (fd < 0 || !line)
		return (-1);
	buf = ft_strnew(BUFF_SIZE);
	if (str == NULL)
		str = ft_strnew(1);
	while (ft_checknline(str) != 1 && (ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		str = ft_stockbuf(str, buf);
		ft_bzero(buf, BUFF_SIZE + 1);
	}
	free(buf);
	if ((*line = ft_strline(str)) == NULL || ret < 0)
		return (-1);
	if (!*str)
		return (0);
	str = ft_strrest(str);
	return (1);
}
