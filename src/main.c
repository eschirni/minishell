/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:31:18 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/17 17:53:20 by eschirni         ###   ########.fr       */
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
		//parser, etc
		commands = malloc(1 * sizeof(char *)); //Parser should return this, so I thought it is kind of practical to do this that way
		commands[0] = malloc(1 * sizeof(char *));
		commands[0][0] = line;
		//if you want to test options
		commands[0][1] = ft_strcdup("src/", '\0', 0);
		executer(envp, commands);
		free(commands[0][0]);
		free(commands[0]);
		free(commands);
	}
}
