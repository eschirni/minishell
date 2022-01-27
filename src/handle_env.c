/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:32:06 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/27 21:05:57 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_env	*new_node(void)
{
	t_env *new;

	new = malloc(sizeof(t_env));
	new->name = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

void	free_env(t_env **env)
{
	t_env	*tmp;
	t_env	*next;

	while (*env != NULL)
	{
		next = (*env)->next;
		free((*env)->name);
		free((*env)->value);
		free(*env);
		*env = next;
	}
	*env = NULL;
}


char	*get_value(t_env *env, char *name)
{
	if (env != NULL && ft_strcmp(env->name, name) == 0)
		return (env->value);
	while (env != NULL && ft_strcmp(env->name, name) != 0)
		env = env->next;
	if (env == NULL)
		return (NULL);
	return (env->value);
}

void	get_env(t_env **env, char **envp) //free split
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
