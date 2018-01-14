/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macuguen <macuguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/20 23:06:25 by macuguen          #+#    #+#             */
/*   Updated: 2018/01/14 03:15:26 by macuguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int				next_of_read(char **new, char **str)
{
	char		*tmp;

	if (*str == NULL)
		*str = ft_strdup(*new);
	else
	{
		tmp = ft_strjoin(*str, *new);
		ft_strdel(str);
		*str = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
	ft_strdel(new);
	return (0);
}

int				read_stdi(int fd, char **str)
{
	char		c[BUFF_SIZE + 1];
	int			size;
	size_t		i;
	char		*new;

	new = NULL;
	while ((size = read(fd, c, BUFF_SIZE)))
	{
		if (size == -1)
			return (-1);
		i = 0;
		c[size] = '\0';
		new = ft_realloc(new, c);
		while (new[i++] != '\0')
		{
			if (new[i] == '\n')
				return (next_of_read(&new, str));
		}
	}
	if (size == 0 && new != NULL)
		next_of_read(&new, str);
	return (1);
}

static	int		ma_fonction(char **line, char **str)
{
	size_t	size;
	char	*tmp;

	size = 0;
	if (ft_search_one_carac(*str, '\n') == 1)
		size = ft_strlen_search_tow(*str, '\n', '\0');
	else
		size = ft_strlen(*str);
	*line = ft_strsub(*str, 0, size);
	if (!(size = ft_strlen(*str) - ft_strlen_search_tow(*str, '\n', '\0')))
		return (0);
	tmp = ft_strsub(*str, (ft_strlen_search_tow(*str, '\n', '\0') + 1), size);
	ft_strdel(str);
	*str = ft_strdup(tmp);
	ft_strdel(&tmp);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char		*str = NULL;
	int				size;
	int				pls;

	pls = read_stdi(fd, &str);
	if ((fd < 0 || line == NULL || BUFF_SIZE <= 0))
		return (-1);
	if ((size = ft_search_one_carac(str, '\n')) == 1)
	{
		ma_fonction(line, &str);
		return (1);
	}
	if (pls == 1 && (str && *str && (size = ft_search_one_carac(str, '\n'))
	== 0))
	{
		pls = ft_strlen(str);
		*line = ft_strsub(str, 0, pls);
		ft_strdel(&str);
		return (1);
	}
	else if (pls == -1)
		return (-1);
	else if (pls == 0)
		ma_fonction(line, &str);
	return (0);
}
