/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:20:43 by tom               #+#    #+#             */
/*   Updated: 2022/02/26 16:36:01 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_process(int *fd, int *tmp)
{
	wait(NULL);
	close(fd[1]);
	*tmp = fd[0];
}

static void	pipe_middle(char *input, int *fd, char **envp, t_env *env_v, int *tmp)
{
	char	**split;

	dup2(*tmp, 0);
	dup2(fd[1], 1); // redirects stdout to pipe write end
	close(fd[0]);
	split = ft_split(input, ' ');
	executer(envp, split, env_v);
	free(split);
	exit(1);
}

static void	pipe_last(char *input, int *fd, char **envp, t_env *env_v, int *tmp)
{
	char	**split;

	dup2(*tmp, 0);
	close(fd[0]);
	split = ft_split(input, ' ');
	executer(envp, split, env_v);
	ft_free_split(split);
	exit(1);
}

static char	**split_tokens(t_token *tokens)
{
	char	**ret;
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 1;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
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
		if (tmp->type == PIPE)
			tmp = tmp->next;
		ret[i] = ft_strdup(tmp->value);
		tmp = tmp->next;
		while (tmp != NULL && tmp->type != PIPE)
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

void	ft_pipe(t_token *tokens, char **envp, t_env *env_v)
{
	int		fd[2];
	int		i;
	int		tmp;
	pid_t	pid;
	char	**input;

	i = 0;
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
				pipe_last(input[i], fd, envp, env_v, &tmp);
			else
				pipe_middle(input[i], fd, envp, env_v, &tmp);
		}
		else
			parent_process(fd, &tmp);
		i++;
	}
	close(fd[0]);
	close(fd[1]);
	ft_free_split(input);
}
