/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:31:18 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/27 21:30:22 by eschirni         ###   ########.fr       */
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
	else
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b", 4);
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
	signal(SIGQUIT, handler);
	while (true)
	{
		line = readline("minishell$ ");
		if (line != NULL)
			add_history(line);
		else
			ft_exit(NULL, true, env);
		//parser, etc
		input = ft_split(line, ' ');
		if (input[0] != '\0')
			executer(envp, input, env);
		ft_free_split(input);
		free(line);
	}
}
