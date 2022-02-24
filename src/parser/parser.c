/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:42:36 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/24 22:32:02 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static bool	safe_redirections(t_token *tokens, int type, int type1, int *arr)
{
	int		i;
	t_token	*tmp;

	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type == type || tmp->type == type1)
		{
			arr[i] = redirections(tmp->next->value, tmp->type);
			if (arr[i] == -1)
				return (false);
			i++;
		}
		tmp = tmp->next;
	}
	arr[i] = -1;
	return (true);
}

static int	**create_array(t_token *tokens)
{
	int	**arr;
	int	i;
	bool	no_error;

	arr = ft_calloc(2, sizeof(int *));
	if (arr == NULL)
		return (NULL);
	i =  count_redirections(tokens, INPUT, HEREDOC);
	arr[0] = ft_calloc(i + 1, sizeof(int));
	i =  count_redirections(tokens, TRUNC, APPEND);
	arr[1] = ft_calloc(i + 1, sizeof(int));
	if (arr[0] == NULL || arr[1] == NULL)
		return (NULL);
	no_error = safe_redirections(tokens, INPUT, HEREDOC, arr[0]);
	if (no_error == true)
		no_error = safe_redirections(tokens, TRUNC, APPEND, arr[1]);
	if (no_error == false)
	{
		free(arr[0]);
		free(arr[1]);
		free(arr);
		return (NULL);
	}
	return (arr);
}

static int	get_fd(int	*arr)
{
	int	i;

	i = 0;
	while (arr[i] != -1)
	{
		if (arr[i + 1] == -1)
			return(arr[i]);
		close(arr[i]);
		i++;
	}
	return (-1);
}

static void	parse_redirections(char *line, char **envp, t_env *env_v, t_token *tokens)
{
	char	**input;
	int		pid;
	int		fd_in;
	int		fd_out;
	int		**arr;

	arr = create_array(tokens);
	if (arr == NULL)
		return ;
	fd_in = get_fd(arr[0]);
	fd_out = get_fd(arr[1]);
	pid = fork();
	if (pid == 0)
	{
		// call dup2 with in/out if arr not empty
		// convert tokens till redirection
		if (fd_in != -1)
			dup2(fd_in, STDIN_FILENO);
		if (fd_out != -1)
			dup2(fd_out, STDOUT_FILENO);
		input = ft_calloc(2, sizeof(char *));
		input[0] = ft_strdup("cat");
		input[1] = NULL;
		if (input[0] != NULL)
			executer(envp, input, env_v);
		ft_free_split(input);
		exit(0);
	}
	else
	{
		close(fd_in);
		close(fd_out);
		wait (NULL);
	}
	free(arr[0]);
	free(arr[1]);
	free(arr);
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
