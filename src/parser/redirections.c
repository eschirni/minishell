/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:52:08 by tom               #+#    #+#             */
/*   Updated: 2022/02/26 21:18:28 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_fd(int og_fd, char *operator)
{
	if (ft_strcmp(operator, "<") == 0)
		dup2(STDIN_FILENO, og_fd);
	else if (ft_strcmp(operator, ">") == 0 || ft_strcmp(operator, ">>") == 0)
		dup2(STDOUT_FILENO, og_fd);
}

static int	re_input(char *right, int fd)
{
	fd = access(right, F_OK);
	if (fd == -1)
	{
		ft_write_error(NULL, right, "No such file or directory");
		return (-1);
	}
	fd = open(right, O_RDONLY, 0777);
	if (fd == -1)
	{
		ft_write_error(NULL, right, "Permission denied");
		return (-1);
	}
	return (fd);
}

static int	re_output(char *right, int fd)
{
	fd = open(right, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		ft_write_error(NULL, right, "Permission denied");
		return (-1);
	}
	return (fd);
}

int	redirections(char *right, int type)
{
	int	fd;

	fd = 0;
	if (type == INPUT || type == HEREDOC)
		return (re_input(right, fd));
	else if (type == TRUNC)
		return (re_output(right, fd));
	else if (type == APPEND)
	{
		fd = open(right, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
		{
			ft_write_error(NULL, right, "Permission denied");
			return (-1);
		}
		return (fd);
	}
	return (-1);
}
