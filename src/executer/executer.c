/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 19:18:33 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/01 21:01:55 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	own_function(char *s)
{
	if (ft_strcmp(s, "cd") == 0 || ft_strcmp(s, "export") == 0)
		return (true);
	else if (ft_strcmp(s, "unset") == 0 || ft_strcmp(s, "exit") == 0)
		return (true);
	else if (ft_strcmp(s, "pwd") == 0 || ft_strcmp(s, "env") == 0)
		return (true);
	return (false);
}

static int	fork_execute(char *path, char **args, char **envp)
{
	pid_t	pid;
	int		error;

	pid = fork();
	if (pid == 0)
		exit(execve(path, args, envp));
	else
		wait(&error); //catching signal sent by exit of(child)
	error /= 255;
	return (error);
}

static void	exec_path(char **commands, char **envp, t_env *env_v)
{
	int		error;
	int		i;
	char	*path;
	char	**path_vars;

	i = 0;
	error = fork_execute(commands[0], commands, envp);
	path_vars = ft_split(get_value(env_v, "PATH"), ':'); //segfault (remove search_name from header)
	while (error > 1 && path_vars[i] != NULL)
	{
		path = ft_strdup(commands[0]);
		path = ft_insert("/", path);
		path = ft_insert(path_vars[i], path);
		error = fork_execute(path, commands, envp);
		free(path);
		i++;
	}
	ft_free_split(path_vars);
	if (error > 1)
		ft_write_error(NULL, commands[0], "command not found");
}

static void	exec_functions(char **command, t_env *env_v)
{
	if (ft_strcmp(command[0], "cd") == 0)
		cd(command[1]);
	else if (ft_strcmp(command[0], "pwd") == 0)
		pwd();
	else if (ft_strcmp(command[0], "export") == 0)
		export(env_v, command[1]);
	else if (ft_strcmp(command[0], "env") == 0)
		env(env_v, command[1]);
	else if (ft_strcmp(command[0], "unset") == 0)
		unset(&env_v, command[1]);
	else
		ft_exit(command, false, env_v);
}

//TODO: add paths to the right commands, /usr/bin for env /bin for ls, etc
void	executer(char **envp, char **commands, t_env *env_v)
{
	if (own_function(commands[0]) == true)
		exec_functions(commands, env_v);
	else
		exec_path(commands, envp, env_v);
}
