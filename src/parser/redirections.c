/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:52:08 by tom               #+#    #+#             */
/*   Updated: 2022/02/23 17:23:47 by eschirni         ###   ########.fr       */
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
	int	tmp_in;

	fd = open(right, O_RDONLY, 0777);
	if (fd == -1)
		return (-1); // error message
	tmp_in = dup(STDIN_FILENO);
	dup2(fd, STDIN_FILENO);
	return (fd);
}

static int	re_output(char *right, int fd)
{
	int	tmp_out;

	fd = open(right, O_RDWR | O_CREAT | O_TRUNC, 0777); // number for file perms
	if (fd == -1)
		return (-1); // error message
	tmp_out = dup(STDOUT_FILENO);
	dup2(fd, STDOUT_FILENO);
	return (fd);
}

int	redirections(char *left, char *right, char *operator)
{
	int	fd;
	int	tmp_out;

	if (ft_strcmp(operator, "<") == 0)
		return (re_input(right, fd));
	else if (ft_strcmp(operator, ">") == 0)
		return (re_output(right, fd));
	else if (ft_strcmp(operator, ">>") == 0)
	{
		fd = open(right, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
			return (-1); // error message
		tmp_out = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		return (fd);
	}
	return (-1);
}
