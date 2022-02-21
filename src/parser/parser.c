/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:42:36 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/21 05:49:03 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parser(char *line, char **envp, t_env *env_v)
{
	char	**input;
	t_token	*tokens;

	line = env_vars(line, env_v);
	line = remove_spaces(line);
	tokens = lexer(ft_split(line, ' '));
	replace_grep(tokens);
	remove_quotes(tokens);
	if (check_redirections(line) == true && check_quotes(line) == true)
	{
		if (count_pipes(tokens) > 0)
		{
			input = ft_split(line, '|');
			if (input[0] != NULL)
				ft_pipe(input, count_pipes(tokens), envp, env_v);
		}
		else
		{
			input = ft_split(line, ' ');
			if (count_redirections(line) > 0)
				exec_redirections(input, envp, env_v);
			else if (input[0] != NULL)
				executer(envp, input, env_v);
		}
		ft_free_split(input);
	}
	ft_free_tokens(tokens);
	free(line);
}
