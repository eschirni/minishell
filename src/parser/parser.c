/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:42:36 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/26 21:03:07 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	remove_heredoc(t_env *env)
{
	char	**tmp;

	if (access("heredoc", F_OK) == 0)
	{
		tmp = ft_calloc(3, sizeof(char *));
		tmp[2] = NULL;
		tmp[0] = ft_strdup("rm");
		tmp[1] = ft_strdup("heredoc");
		executer(tmp, env);
		ft_free_split(tmp);
	}
}

static void	parse_red_child(t_token *tokens, int fd_in, int fd_out, t_env *env)
{
	char	**input;

	dup2(fd_in, STDIN_FILENO);
	if (fd_out != -1)
		dup2(fd_out, STDOUT_FILENO);
	input = convert_tokens(tokens);
	if (input[0] != NULL)
		executer(input, env);
	ft_free_split(input);
	exit(0);
}

void	parse_redirections(t_env *env, t_token *tokens)
{
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
		parse_red_child(tokens, fd_in, fd_out, env);
	else
	{
		close(fd_in);
		close(fd_out);
		wait (NULL);
	}
	free(arr[0]);
	free(arr[1]);
	free(arr);
	remove_heredoc(env);
}

void	parser(char *line, t_env *env)
{
	t_token	*tokens;
	char	**input;

	line = env_vars(line, env->env_v);
	line = remove_spaces(line);
	tokens = lexer(ft_split(line, ' '));
	if (line[0] != '\0' && check_redirections(line) && check_quotes(line))
	{
		remove_quotes(tokens);
		if (has_pipes(tokens) == true)
			ft_pipe(tokens, env, 0);
		else if (has_redirections(tokens) == true)
			parse_redirections(env, tokens);
		else
		{
			input = convert_tokens(tokens);
			if (input != NULL && input[0] != NULL)
				executer(input, env);
			if (input != NULL)
				ft_free_split(input);
		}
	}
	ft_free_tokens(tokens);
	free(line);
}
