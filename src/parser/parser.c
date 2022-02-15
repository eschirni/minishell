/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:42:36 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/15 21:43:12 by eschirni         ###   ########.fr       */
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
		if (count_pipes(line) == 0)
		{
			input = ft_split(line, ' ');
			if (input[0] != '\0')
				executer(envp, input, env_v);
		}
		else
		{
			input = ft_split(line, '|');
			if (input[0] != '\0')
				ft_pipe(input, count_pipes(line), envp, env_v);
		}
		ft_free_split(input);
	}
	free(line);
}
