/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 19:18:33 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/17 17:44:48 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

static void	exec_functions(char *function, char **args) //this is garbage too
{
	if (ft_strcmp(function, "cd") == 0)
		cd(args[1]);
	if (ft_strcmp(function, "export") == 0)
		return ;
	else
		return ;
}

//Bugs: doesn't execute the command all the time
//TODO: add paths to the right commands, /usr/bin for env /bin for ls, etc
void	executer(char **envp, char ***commands)
{
	int	pid;

	if (ft_strcmp(commands[0][0], "cd") == 0 || ft_strcmp(commands[0][0], "export") == 0 || ft_strcmp(commands[0][0], "unset") == 0)
		exec_functions(commands[0][0], commands[0]);
	else
	{
		commands[0][0] = ft_insert("/bin/", commands[0][0]);
		pid = fork();
		if (pid == 0)
		{
			execve(commands[0][0], commands[0], envp);
		}
		else
			wait(NULL); //waits until all child processes are terminated
	}
}
