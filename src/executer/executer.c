/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 19:18:33 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/15 20:08:16 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

static void	exec_functions(char *function, char **args) //this is garbage too
{
	if (strncmp(function, "exit", 4) == 0)
		ft_exit(args[1]);
}

void	executer(char **envp, char ***commands)
{
	//following is just bullshit, NOT THE EXECUTER AS IT'S SUPPOSED TO BE
	if (strncmp(commands[0][0], "env", 3) == 0 || strncmp(commands[0][0], "cd", 2) == 0 || strncmp(commands[0][0], "export", 6) == 0 || strncmp(commands[0][0], "unset", 5) == 0 || strncmp(commands[0][0], "exit", 4) == 0)
		exec_functions(commands[0][0], commands[0]);
	else
	{
		commands[0][0] = ft_insert("/bin/", commands[0][0]);
		execve(commands[0][0], commands[0], envp);
	}
}
