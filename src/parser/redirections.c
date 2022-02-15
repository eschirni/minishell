/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:52:08 by tom               #+#    #+#             */
/*   Updated: 2022/02/15 22:29:33 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirections(char *left, char *right, char *operator)
{
	int	fd;

	if (ft_strcmp(operator, "<") == 0)
	{
		fd = open(right, O_RDONLY);
		if (fd == -1)
			return 1; // error message
		dup2(fd, STDIN_FILENO);
	}
	else if (ft_strcmp(operator, ">") == 0)
	{
		fd = open(left, O_RDWR, O_CREAT, O_TRUNC, 0664); // number for file perms
		if (fd == -1)
			return 1; // error message
		dup2(fd, STDOUT_FILENO);
	}
	else if (ft_strcmp(operator, ">>") == 0)
	{
		fd = open(left, O_RDWR, O_CREAT, O_APPEND, 0664);
		if (fd == -1)
			return 1; // error message
		dup2(fd, STDOUT_FILENO);
	}
	return (0);
}
