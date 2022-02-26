/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 18:32:06 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/26 21:19:09 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_v	*new_node(void)
{
	t_env_v	*new;

	new = malloc(sizeof(t_env_v));
	new->name = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

void	free_env(t_env_v **env_v)
{
	t_env_v	*next;

	while (*env_v != NULL)
	{
		next = (*env_v)->next;
		free((*env_v)->name);
		free((*env_v)->value);
		free(*env_v);
		*env_v = next;
	}
	*env_v = NULL;
}

bool	search_env(t_env_v *env_v, char *name)
{
	while (env_v != NULL)
	{
		if (ft_strcmp(name, env_v->name) == 0)
			return (true);
		env_v = env_v->next;
	}
	return (false);
}

char	*get_value(t_env_v *env_v, char *name)
{
	if (env_v != NULL && ft_strcmp(env_v->name, name) == 0)
		return (env_v->value);
	while (env_v != NULL && ft_strcmp(env_v->name, name) != 0)
		env_v = env_v->next;
	if (env_v == NULL)
		return (NULL);
	return (env_v->value);
}

void	init_env(t_env_v **env_v, char **envp)
{
	t_env_v	*tmp;
	int		i;
	char	**split_string;

	i = 0;
	*env_v = new_node();
	tmp = *env_v;
	while (envp[i] != NULL)
	{
		split_string = ft_split(envp[i], '=');
		(*env_v)->name = ft_strdup(split_string[0]);
		(*env_v)->value = ft_strdup(split_string[1]);
		(*env_v)->export = true;
		ft_free_split(split_string);
		if (envp[i + 1] == NULL)
			break ;
		(*env_v)->next = new_node();
		(*env_v) = (*env_v)->next;
		i++;
	}
	*env_v = tmp;
}
