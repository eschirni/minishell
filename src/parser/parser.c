/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:42:36 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/23 17:37:48 by eschirni         ###   ########.fr       */
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
		int df;
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
	line = remove_spaces(line);
	tokens = lexer(ft_split(line, ' '));
	replace_grep(tokens);
	remove_quotes(tokens);
	if (tokens != NULL && check_redirections(line) && check_quotes(line))
	{
		if (has_redirections(tokens) == true)
			parse_redirections(line, envp, env_v);
		else
		{
			input = ft_split(line, ' ');
			executer(envp, input, env_v);
			ft_free_split(input);
		}
			
	}
	ft_free_tokens(tokens);
	free(line);
}
