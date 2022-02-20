/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:44:28 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/21 00:11:24 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_write_error(char *command, char *arg, char *error)
{
	pid_t	fd;

	fd = fork();
	if (fd == 0)
	{
		dup2(STDERR_FILENO, STDOUT_FILENO);
		printf(RED "minishell: ");
		if (command != NULL)
			printf("%s: ", command);
		if (arg != NULL)
			printf("%s: ", arg);
		printf("%s\n", error);
		exit(0);
	}
	else
		wait(NULL);
}
