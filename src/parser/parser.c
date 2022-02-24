/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:42:36 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/24 19:09:07 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	safe_redirections(t_token *tokens, int type, int type1, int *arr)
{
	int		i;
	t_token	*tmp;

	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type == type || tmp->type == type1)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static int	count_redirections(t_token *tokens, int type, int type1)
{
	int		i;
	t_token	*tmp;

	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type == type || tmp->type == type1)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static int	**create_array(t_token *tokens)
{
	int	**arr;
	int	i;

	arr = ft_calloc(3, sizeof(int *));
	if (arr == NULL)
		return (NULL);
	arr[2] = NULL;
	i =  count_redirections(tokens, INPUT, HEREDOC);
	arr[0] = ft_calloc(i + 1, sizeof(int));
	i =  count_redirections(tokens, TRUNC, APPEND);
	arr[1] = ft_calloc(i + 1, sizeof(int));
	if (arr[0] == NULL || arr[1] == NULL)
		return (NULL);
	return (arr);
}

static void	parse_redirections(char *line, char **envp, t_env *env_v, t_token *tokens)
{
	char	**input;
	int		pid;
	int		fd;

	create_array(tokens);
	// pid = fork();
	// if (pid == 0)
	// {
	// 	fd = redirections("cat Makefile", "test", ">");
	// 	input = ft_split(line, ' ');
	// 	if (input[0] != NULL)
	// 		executer(envp, input, env_v);
	// 	close(fd);
	// 	ft_free_split(input);
	// 	ft_free_split(input);
	// 	exit(0);
	// }
	// else
	// 	wait (NULL);
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
			parse_redirections(line, envp, env_v, tokens);
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
