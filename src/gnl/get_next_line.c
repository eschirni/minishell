/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/06 21:16:35 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/15 14:15:46 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_delall(char **a)
{
	free(*a);
	*a = NULL;
	return (NULL);
}

static void	ft_reading(char **rest, int fd)
{
	char	*buffer;
	int		val;

	buffer = ft_calloc(BUFFER_SIZE + 1);
	val = read(fd, buffer, BUFFER_SIZE);
	while (val > 0)
	{
		buffer[val] = '\0';
		if (*rest == NULL)
			*rest = ft_strcdup(buffer, '\0', 0);
		else
			*rest = ft_append(*rest, buffer);
		if (ft_strchr(*rest, '\n') != NULL)
			break ;
		val = read(fd, buffer, BUFFER_SIZE);
	}
	if (val < 0)
		ft_delall(rest);
	ft_delall(&buffer);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*temp;
	char		*ret;

	if (fd < 0)
		return (NULL);
	ft_reading(&rest, fd);
	if (rest == NULL || rest[0] == '\0')
		return (NULL);
	else if (ft_strchr(rest, '\n') != NULL)
	{
		ret = ft_strcdup(rest, '\n', 0);
		temp = ft_strcdup(rest, '\0', ft_strclen(rest, '\n') + 1);
		free(rest);
		rest = temp;
		if (rest[0] == '\0')
			ft_delall(&rest);
	}
	else
	{
		ret = ft_strcdup(rest, '\0', 0);
		ft_delall(&rest);
	}
	return (ret);
}
