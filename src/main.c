/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:12:54 by tom               #+#    #+#             */
/*   Updated: 2022/01/26 18:12:57 by tom              ###   ########.fr       */
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
