/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:31:18 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/26 14:30:39 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b\n", 5);
		rl_on_new_line();
		rl_redisplay();
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
	signal(SIGINT, handler);
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
