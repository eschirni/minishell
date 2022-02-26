/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:20:43 by tom               #+#    #+#             */
/*   Updated: 2022/02/26 20:51:59 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_process(int *fd, int *tmp)
{
	wait(NULL);
	close(fd[1]);
	*tmp = fd[0];
}

static void	pipe_middle(char *input, int *fd, t_env *env, int *tmp)
{
	char	**split;

	dup2(*tmp, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	split = ft_split(input, ' ');
	executer(split, env);
	free(split);
	exit(1);
}

static void	pipe_last(t_token *tokens, int *fd, t_env *env, int *tmp)
{
	char	**split;
	t_token	*tmp_tokens;

	dup2(*tmp, 0);
	close(fd[0]);
	tmp_tokens = after_pipe(tokens);
	if (has_redirections(tmp_tokens) == true)
		parse_redirections(env, tmp_tokens);
	else
	{
		split = convert_tokens(tmp_tokens);
		executer(split, env);
		ft_free_split(split);
	}
	exit(1);
}

static void	free_and_close(int *fd, char **input)
{
	close(fd[0]);
	close(fd[1]);
	ft_free_split(input);
}

void	ft_pipe(t_token *tokens, t_env *env, int i)
{
	int		fd[2];
	int		tmp;
	pid_t	pid;
	char	**input;

	tmp = 0;
	input = split_tokens(tokens);
	while (input[i] != NULL)
	{
		if (pipe(fd) == -1)
			exit(1);
		pid = fork();
		if (pid == 0)
		{
			if (input[i + 1] == NULL)
				pipe_last(tokens, fd, env, &tmp);
			else
				pipe_middle(input[i], fd, env, &tmp);
		}
		else
			parent_process(fd, &tmp);
		i++;
	}
	free_and_close(fd, input);
}
