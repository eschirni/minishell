/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:42:36 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:06 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parse_redirections(char *line, char **envp, t_env *env_v)
{
	char	**input;
	int		pid;
	int		fd;

	pid = fork();
	if (pid == 0)
	{
		fd = redirections("cat Makefile", "test", ">");
		input = ft_split(line, ' ');
		if (input[0] != NULL)
			executer(envp, input, env_v);
		close(fd);
		ft_free_split(input);
		ft_free_split(input);
		exit(0);
	}
	else
		wait (NULL);
}

void	parser(char *line, char **envp, t_env *env_v)
{
	t_token	*tokens;
	char	**input;

	line = env_vars(line, env_v);
	line = replace_grep(line);
	line = remove_spaces(line);
	tokens = lexer(ft_split(line, ' '));
	if (line[0] != '\0' && check_redirections(line) && check_quotes(line))
	{
		remove_quotes(tokens);
		if (has_redirections(tokens) == true)
			parse_redirections(line, envp, env_v);
		else
		{
			input = convert_tokens(tokens);
			if (input != NULL && input[0] != NULL)
				executer(envp, input, env_v);
			if (input != NULL)
				ft_free_split(input);
		}
	}
	ft_free_tokens(tokens);
	free(line);
}
