/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:31:18 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/03 20:41:08 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handler(int signal)
{
	rl_on_new_line();
	rl_redisplay();
	if (signal == SIGINT)
		write(1, "  \b\b\n", 5);
	else
		write(1, "  \b\b", 4);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
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
