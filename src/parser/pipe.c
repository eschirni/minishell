/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:20:43 by tom               #+#    #+#             */
/*   Updated: 2022/02/26 20:27:49 by eschirni         ###   ########.fr       */
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

static	t_token *after_pipe(t_token *tokens)
{
	t_token	*tmp;
	t_token	*end;

	end = tokens;
	while (end != NULL)
	{
		if (end->type == PIPE)
			tmp = end->next;
		end = end->next;
	}
	return (tmp);
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

static char	**split_tokens(t_token *tokens, int type)
{
	char	**ret;
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 1;
	while (tmp != NULL)
	{
		if (tmp->type == type)
		{
			i++;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	ret = ft_calloc(i + 1, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type == type)
			tmp = tmp->next;
		ret[i] = ft_strdup(tmp->value);
		tmp = tmp->next;
		while (tmp != NULL && tmp->type != type)
		{
			ret[i] = ft_append(ret[i], " ");
			ret[i] = ft_append(ret[i], tmp->value);
			tmp = tmp->next;
		}
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	ft_pipe(t_token *tokens, t_env *env)
{
	int		fd[2];
	int		i;
	int		tmp;
	pid_t	pid;
	char	**input;

	i = 0;
	tmp = 0;
	input = split_tokens(tokens, PIPE);
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
	close(fd[0]);
	close(fd[1]);
	ft_free_split(input);
}
