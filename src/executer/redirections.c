/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:52:08 by tom               #+#    #+#             */
/*   Updated: 2022/02/16 12:56:22 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	redirections(char *left, char *right, char *operator)
{
	int	fd;

	if (ft_strcmp(operator, "<") == 0)
	{
		fd = open(right, O_RDONLY, 0777);
		if (fd == -1)
			return 1; // error message
		dup2(fd, STDIN_FILENO);
	}
	else if (ft_strcmp(operator, ">") == 0)
	{
		fd = open(right, O_RDWR | O_CREAT | O_TRUNC, 0777); // number for file perms
		if (fd == -1)
			return 1; // error message
		dup2(fd, STDOUT_FILENO);
	}
	else if (ft_strcmp(operator, ">>") == 0)
	{
		fd = open(right, O_RDWR | O_CREAT | O_APPEND, 0777);
		if (fd == -1)
			return 1; // error message
		dup2(fd, STDOUT_FILENO);
	}
	return (0);
}