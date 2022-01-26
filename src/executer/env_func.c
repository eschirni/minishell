/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:28:57 by tom               #+#    #+#             */
/*   Updated: 2022/01/26 14:03:17 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

bool	search_env(t_env *env, char *name)
{
	while (env != NULL)
	{
		if (ft_strcmp(name, env->name) == 0)
			return (true);
		env = env->next;
	}
	return (false);
}

t_env	*new_node(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->name = NULL;
	new->value = NULL;
	new->export = false;
	new->next = NULL;
	return (new);
}

void	export_env(t_env **env, char *name)
{
	t_env	*tmp;

	tmp = *env;
	if (tmp != NULL && ft_strcmp(tmp->name, name) == 0)
	{
		tmp->export = true;
		return ;
	}
	while (tmp != NULL && ft_strcmp(tmp->name, name) != 0)
	{
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	tmp->export = true;
}

void	print_env(t_env *env)
{
	while (env != NULL)
	{
		if (env->export == true)
			printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

t_env	*sort_env(t_env *env)
{
	t_env	*current;
	t_env	*index;
	char	*name_tmp;
	char	*value_tmp;

	current = env;
	index = NULL;
	while (current != NULL)
	{
		index = current->next;
		while (index != NULL)
		{
			if (ft_strcmp(current->name, index->name) > 0) //string a is smaller then string b
			{
				name_tmp = current->name;
				value_tmp = current->value;
				current->name = index->name;
				current->value = index->value;
				index->name = name_tmp;
				index->value = value_tmp;
			}
			index = index->next;
		}
		current = current->next;
	}
	return (env);
}

void	print_export(t_env *env)
{
	env = sort_env(env);
	while (env != NULL)
	{
		if (env->export == true)
			printf("declare -x %s=\"%s\"\n", env->name, env->value);
		env = env->next;
	}
}

void	add_env(t_env **env, char *name, char *value, bool export)
{
	t_env	*new;

	new = new_node();
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->export = export;
	ft_lstadd_back(env, new);
}

void	del_env(t_env **env, char *name)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	if (tmp != NULL && ft_strcmp(tmp->name, name) == 0)
	{
		*env = tmp->next; // Changed head
		free(tmp); // free old head
		return ;
	}
	while (tmp != NULL && ft_strcmp(tmp->name, name) != 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	free(tmp); // Free memory
}

void	rep_env(t_env **env, char *name, char *value, bool export)
{
	t_env	*tmp;

	tmp = *env;
	if (tmp != NULL && ft_strcmp(tmp->name, name) == 0)
	{
		free(tmp->value);
		tmp->value = ft_strdup(value);
		tmp->export = export;
		return ;
	}
	while (tmp != NULL && ft_strcmp(tmp->name, name) != 0)
	{
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	free(tmp->value);
	tmp->value = ft_strdup(value);
	tmp->export = export;
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

void	init_env(t_env **env, char **envp)
{
	t_env	*tmp;
	t_env	*node;
	int		i;
	char	**split_string;

	i = 0;
	*env = new_node();
	tmp = *env;
	while (envp[i] != NULL)
	{
		split_string = ft_split(envp[i], '=');
		(*env)->name = ft_strdup(split_string[0]);
		(*env)->value = ft_strdup(split_string[1]);
		(*env)->export = true;
		free_split(split_string);
		if (envp[i + 1] == NULL)
			break ;
		(*env)->next = new_node();
		(*env) = (*env)->next;
		i++;
	}
	*env = tmp;
}