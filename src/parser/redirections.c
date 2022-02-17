/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:52:08 by tom               #+#    #+#             */
/*   Updated: 2022/02/17 14:52:08 by eschirni         ###   ########.fr       */
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

int	redirections(char *left, char *right, char *operator)
{
	int	fd;
	int	tmp_in;
	int	tmp_out;

	if (ft_strcmp(operator, "<") == 0)
	{
		fd = open(right, O_RDONLY, 0777);
		if (fd == -1)
			return (-1); // error message
		tmp_in = dup(STDIN_FILENO);
		dup2(fd, STDIN_FILENO);
		return (tmp_in);
	}
	else if (ft_strcmp(operator, ">") == 0)
	{
		PRINT_HERE();
		fd = open(right, O_RDWR | O_CREAT | O_TRUNC, 0777); // number for file perms
		if (fd == -1)
			return (-1); // error message
		PRINT_HERE();
		tmp_out = dup(STDOUT_FILENO);
		PRINT_HERE();
		dup2(fd, STDOUT_FILENO);
		PRINT_HERE();
		return (tmp_out);
	}
	else if (ft_strcmp(operator, ">>") == 0)
	{
		fd = open(right, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
			return (-1); // error message
		tmp_out = dup(STDOUT_FILENO);
		dup2(fd, STDOUT_FILENO);
		return (tmp_out);
	}
	return (-1);
}