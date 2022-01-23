/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:31:18 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/23 15:56:18 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_env(t_env **env)
{
	t_env	*tmp;

	while (*env != NULL)
	{
		tmp = (*env)->next;
		free((*env)->name);
		free((*env)->value);
		free(*env);
		*env = tmp;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**input;
	int		i;
	t_env	*env;

	if (argc != 1)
	{
		perror("Usage: ./minishell");
		return (1);
	}
	get_env(&env, envp);
	while (true)
	{
		line = readline("minishell$ ");
		if (line != NULL)
			add_history(line);
		else
			ft_exit(NULL, true);
		//parser, etc
		input = ft_split(line, ' ');
		if (input[0] != '\0')
			executer(envp, input, env);
		i = 0;
		while (input[i] != NULL)
		{
			free(input[i]);
			i++;
		}
		free(input);
		free(line);
	}
}
