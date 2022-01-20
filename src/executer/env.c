/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 13:28:57 by tom               #+#    #+#             */
/*   Updated: 2022/01/20 18:19:27 by tom              ###   ########.fr       */
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

t_env	*new_node(void)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->name = NULL;
	new->value = NULL;
	new->next = NULL;
	return (new);
}

void	print_env(t_env *env)
{
	while (env != NULL)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}

void	add_env(t_env **env, char *name, char *value)
{
	t_env	*new;

	new = new_node();
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	ft_lstadd_back(env, new);
}

void	del_env(t_env **env, char *name)
{
	t_env	*tmp;
	t_env	*cache;

	tmp = *env;
	while(ft_strcmp(tmp->name, name) != 0)
		tmp = tmp->next;
	if (tmp->next == NULL)
	{
		free(tmp->next);
		tmp->next = NULL;
		return ;
	}
	cache = tmp->next->next;
	free(tmp->next);
	tmp->next = cache;
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
		free_split(split_string);
		if (envp[i + 1] == NULL)
			break ;
		(*env)->next = new_node();
		(*env) = (*env)->next;
		i++;
	}
	*env = tmp;
}
