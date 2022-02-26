/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 19:18:33 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/26 20:26:38 by eschirni         ###   ########.fr       */
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
	else if (ft_strcmp(s, "echo") == 0)
		return (true);
	return (false);
}

static int	fork_execute(char *path, char **args, t_env *env)
{
	pid_t	pid;
	int		error;

	pid = fork();
	if (pid == 0)
	{
		error = execve(path, args, env->envp);
		exit(error);
	}
	else
		wait(&error);
	error /= 255;
	if (error == 256)
		error = 127;
	rep_env(&env->env_v, ft_strdup("?"), ft_itoa(error), false);
	return (error);
}

static void	exec_path(char **commands, t_env *env)
{
	int		error;
	int		i;
	char	*path;
	char	**path_vars;

	i = 0;
	error = fork_execute(commands[0], commands, env);
	if (get_value(env->env_v, "PATH") == NULL)
	{
		ft_write_error(NULL, commands[0], "No such file or directory");
		return ;
	}
	path_vars = ft_split(get_value(env->env_v, "PATH"), ':');
	while (error == 127 && path_vars[i] != NULL)
	{
		path = ft_strdup(commands[0]);
		path = ft_insert("/", path);
		path = ft_insert(path_vars[i], path);
		error = fork_execute(path, commands, env);
		free(path);
		i++;
	}
	ft_free_split(path_vars);
	if (error == 127)
		ft_write_error(NULL, commands[0], "command not found");
}

static void	exec_functions(char **command, t_env_v *env_v)
{
	if (ft_strcmp(command[0], "cd") == 0)
		cd(command[1], env_v);
	else if (ft_strcmp(command[0], "pwd") == 0)
		pwd(env_v);
	else if (ft_strcmp(command[0], "export") == 0)
		export(env_v, command[1]);
	else if (ft_strcmp(command[0], "env") == 0)
		env(env_v, command[1]);
	else if (ft_strcmp(command[0], "unset") == 0)
		unset(&env_v, command[1]);
	else if (ft_strcmp(command[0], "echo") == 0)
		echo(command, env_v);
	else
		ft_exit(command, false, env_v);
}

void	executer(char **commands, t_env *env)
{
	if (own_function(commands[0]) == true)
		exec_functions(commands, env->env_v);
	else
		exec_path(commands, env);
}
