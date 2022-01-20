/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 19:18:33 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/19 18:46:45 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <string.h>

static t_env	*new_node(void)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	new->name = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

void	get_env(t_env **env, char **envp)
{
	int		i;
	int		j;
	char	**string;
	t_env 	*tmp;

	*env = new_node();
	i = 0;
	tmp = *env;
	while (envp[i] != NULL)
	{
		j = 0;
		string = ft_split(envp[i], '=');
		tmp->name = string[j];
		j++;
		tmp->value = string[j];
		free(string);
		tmp->next = new_node();
		tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
}

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
void	executer(char **envp, char **commands)
{
	int	pid;

	if (ft_strcmp(commands[0], "cd") == 0 || ft_strcmp(commands[0], "export") == 0 || ft_strcmp(commands[0], "unset") == 0)
		exec_functions(commands[0], commands);
	else
	{
		commands[0] = ft_insert("/bin/", commands[0]);
		pid = fork();
		if (pid == 0)
			execve(commands[0], commands, envp);
		else
			wait(NULL); //waits until all child processes are terminated
	}
}
