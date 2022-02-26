/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:42:36 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/26 19:58:29 by tom              ###   ########.fr       */
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
	int		fd;
	t_token	*tmp;
	char	*heredoc;

	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type == type || tmp->type == type1)
		{
			if (tmp->type == HEREDOC)
			{
				heredoc = exec_heredoc(tmp->next->value);
				fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
				write (fd, heredoc, ft_strclen(heredoc, '\0'));
				close(fd);
				free(heredoc);
				arr[i] = redirections("heredoc", HEREDOC);
			}
			else
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
	int		**arr;
	int		i;
	bool	no_error;

	arr = ft_calloc(2, sizeof(int *));
	if (arr == NULL)
		return (NULL);
	i = count_redirections(tokens, INPUT, HEREDOC);
	arr[0] = ft_calloc(i + 1, sizeof(int));
	i = count_redirections(tokens, TRUNC, APPEND);
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
			return (arr[i]);
		close(arr[i]);
		i++;
	}
	return (-1);
}

static void	remove_heredoc(char **envp, t_env *env_v)
{
	char	**tmp;

	if (access("heredoc", F_OK) == 0)
	{
		tmp = ft_calloc(3, sizeof(char *));
		tmp[2] = NULL;
		tmp[0] = ft_strdup("rm");
		tmp[1] = ft_strdup("heredoc");
		executer(envp, tmp, env_v);
		ft_free_split(tmp);
	}
}

void	parse_redirections(char **envp, t_env *env_v, t_token *tokens)
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
		if (fd_in != -1)
			dup2(fd_in, STDIN_FILENO);
		if (fd_out != -1)
			dup2(fd_out, STDOUT_FILENO);
		input = convert_tokens(tokens);
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
	remove_heredoc(envp, env_v);
}

void	parser(char *line, char **envp, t_env *env_v)
{
	t_token	*tokens;
	char	**input;

	line = env_vars(line, env_v);
	line = remove_spaces(line);
	tokens = lexer(ft_split(line, ' '));
	if (line[0] != '\0' && check_redirections(line) && check_quotes(line))
	{
		remove_quotes(tokens);
		if (has_pipes(tokens) == true)
			ft_pipe(tokens, envp, env_v);
		else if (has_redirections(tokens) == true)
			parse_redirections(envp, env_v, tokens);
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
