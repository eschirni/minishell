/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:31:18 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/21 13:06:39 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**input;
	int		i;

	t_env	*env;

	/* init env */
	init_env(&env, envp);
	// printf("----- ORIGINAL ENV -----\n\n");
	// print_env(env);

	/* add env */
	// add_env(&env, "TEST_NAME", "TEST_VALUE");
	// printf("\n\n----- NEW ENV -----\n\n");
	// print_env(env);

	/* rep env */
	// rep_env(&env, "TEST_NAME", "NEW_VALUE");
	// printf("\n\n----- DEL ENV -----\n\n");
	// print_env(env);

	/* del env */
	// del_env(&env, "TEST_ENV");
	// printf("\n\n----- DEL ENV -----\n\n");
	// print_env(env);

	free_env(&env);
	system("leaks minishell");


	// if (argc != 1)
	// {
	// 	perror("Usage: ./minishell");
	// 	return (1);
	// }
	// while (1)
	// {
	// 	line = readline("minishell$ ");
	// 	if (line != NULL)
	// 		add_history(line);
	// 	//parser, etc
	// 	input = ft_split(line, ' ');
	// 	if (input[0] != '\0')
	// 	{
	// 		executer(envp, input);
	// 		i = 0;
	// 		while (input[i] != NULL)
	// 		{
	// 			free(input[i]);
	// 			i++;
	// 		}
	// 		free(input);
	// 	}
	// 	free(line);
	// }
}
