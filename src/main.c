/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:31:18 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/26 19:49:52 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	handler(int signal)
{
	rl_on_new_line();
	rl_redisplay();
	if (signal == SIGINT)
	{
		write(1, "  \b\b\n", 5);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(1, "  \b\b", 4);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_env	*env_v;

	if (argc != 1)
	{
		perror(RED"Usage: ./minishell");
		return (1);
	}
	init_env(&env_v, envp);
	add_env(&env_v, ft_strdup("?"), ft_strdup("0"), false);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	while (true)
	{
		line = readline(BLUE"minishell$ "RESETCOLOR);
		if (line != NULL)
			add_history(line);
		else
			ft_exit(NULL, true, env_v);
		parser(line, envp, env_v);
	}
}
