/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:31:18 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/02 20:59:26 by eschirni         ###   ########.fr       */
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
	int		i;
	t_env	*env_v;

	if (argc != 1)
	{
		perror("Usage: ./minishell");
		return (1);
	}
	init_env(&env_v, envp);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	while (true)
	{
		line = readline("minishell$ ");
		if (line != NULL)
			add_history(line);
		else
			ft_exit(NULL, true, env_v);
		parser(line, envp, env_v);
	}
}
