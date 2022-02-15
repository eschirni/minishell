/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 16:20:43 by tom               #+#    #+#             */
/*   Updated: 2022/02/15 21:38:26 by eschirni         ###   ########.fr       */
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

void	ft_pipe(char **input, int pipe_count, char **envp, t_env *env_v)
{
	int		fd[2];
	int		i;
	int		cmd;
	int		tmp;
	pid_t	pid;

	cmd = 0;
	i = pipe_count;
	while (i >= 0)
	{
		if (pipe(fd) == -1)
			exit(1);
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				pipe_last(input[cmd], fd, envp, env_v, &tmp);
			else
				pipe_middle(input[cmd], fd, envp, env_v, &tmp);
		}
		else
			parent_process(fd, &tmp);
		i--;
		cmd++;
	}
	close(fd[0]);
	close(fd[1]);
}
