/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:42:36 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/17 13:46:24 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parser(char *line, char **envp, t_env *env_v)
{
	char	**input;

	line = env_vars(line, env_v);
	//remove leftover spaces
	//remove " and '
	if (check_redirections(line) == true)
	{
		if (count_pipes(line) > 0)
		{
			input = ft_split(line, '|');
			if (input[0] != NULL) // changed to NULL to silence warnings
				ft_pipe(input, count_pipes(line), envp, env_v);
		}
		else
		{
			input = ft_split(line, ' ');
			if (count_redirections(line) > 0)
				exec_redirections(input, envp, env_v);
			else if (input[0] != NULL) // changed to NULL to silence warnings
				executer(envp, input, env_v);
		}
		ft_free_split(input);
	}
	free(line);
}
