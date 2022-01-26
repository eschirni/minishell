/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 20:31:18 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/26 15:59:54 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	init_env(&env, envp);
	export(&env, "name=new_value");
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
