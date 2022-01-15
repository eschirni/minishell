/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:31:18 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/15 20:08:08 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	***commands;

	if (argc != 1)
	{
		perror("Usage: ./minishell");
		return (1);
	}
	while (1)
	{
		line = readline("minishell$ ");
		if (line != NULL)
			add_history(line);
		free(line);
		//parser, etc
		commands = malloc(3 * sizeof(char *));
		commands[0] = malloc(3 * sizeof(char *));
		commands[0][0] = malloc(3 * sizeof(char));
		commands[0][1] = malloc(2 * sizeof(char));
		commands[0][0][0] = 'l';
		commands[0][0][1] = 's';
		commands[0][0][2] = '\0';
		commands[0][1][0] = '.';
		commands[0][1][1] = '\0';
		executer(envp, commands);
	}
}
