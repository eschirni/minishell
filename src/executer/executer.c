/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 19:18:33 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/21 12:56:37 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#include <string.h>

static int	fork_execute(char *path, char **args, char **envp)
{
	int		pid;
	int		error;

	pid = fork();
	if (pid == 0)
		exit(execve(path, args, envp));
	else
		wait(&error); //catching signal sent by exit of(child)
	error /= 255;
	return (error);
}

static void	exec_path(char **commands, char **envp, t_env *env)
{
	int		error;
	int		i;
	char	*path;
	char	**path_vars;

	i = 0;
	error = fork_execute(commands[0], commands, envp);
	path_vars = ft_split(get_value(env, "PATH"), ':');
	while (error > 1 && path_vars[i] != NULL)
	{
		path = strdup(commands[0]); //TODO
		path = ft_insert("/", path);
		path = ft_insert(path_vars[i], path);
		error = fork_execute(path, commands, envp);
		free(path);
		i++;
	}
	i = 0;
	while (path_vars[i] != NULL)
	{
		free(path_vars[i]);
		i++;
	}
	free(path_vars);
	if (error > 1)
		ft_write_error(NULL, commands[0], "command not found");
}

static void	exec_functions(char *function, char **args)
{
	if (ft_strcmp(function, "cd") == 0)
		cd(args[1]);
	if (ft_strcmp(function, "export") == 0)
		return ;
	else
		return ;
}

//TODO: add paths to the right commands, /usr/bin for env /bin for ls, etc
void	executer(char **envp, char **commands, t_env *env)
{
	if (ft_strcmp(commands[0], "cd") == 0 || ft_strcmp(commands[0], "export") == 0 || ft_strcmp(commands[0], "unset") == 0 || ft_strcmp(commands[0], "exit") == 0)
		exec_functions(commands[0], commands);
	else
		exec_path(commands, envp, env);
}
