/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:58:13 by tom               #+#    #+#             */
/*   Updated: 2022/01/31 01:28:41 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	export_env(t_env **env, char *name)
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

static void	sort_env(t_env *env_v)
{
	t_env	*current;
	t_env	*index;
	char	*name_tmp;
	char	*value_tmp;

	current = env_v;
	index = NULL;
	while (current != NULL)
	{
		index = current->next;
		while (index != NULL)
		{
			if (ft_strcmp(current->name, index->name) > 0)
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
}

// static void	dup_env(t_env **new, t_env *env_v)
// {
// 	t_env	*tmp;
// 	t_env	*envp_tmp;

// 	*new = new_node();
// 	tmp = *new;
// 	envp_tmp = env_v;
// 	while (envp_tmp != NULL)
// 	{
// 		(*new)->name = ft_strdup(envp_tmp->name);
// 		(*new)->value = ft_strdup(envp_tmp->value);
// 		(*new)->export = envp_tmp->export;
// 		if (envp_tmp->next == NULL)
// 			break ;
// 		(*new)->next = new_node();
// 		(*new) = (*new)->next;
// 		envp_tmp = envp_tmp->next;
// 	}
// 	*new = tmp;
// }

static void	print_export(t_env env_v)
{
	t_env	*tmp;

	tmp = &env_v;
	sort_env(tmp);
	while (tmp != NULL)
	{
		if (tmp->export == true)
			printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

void	export(t_env **env_v, char *arg)
{
	int		pos;
	char	*name;
	char	*value;

	if (arg == NULL)
		print_export(**env_v);
	else
	{
		pos = ft_strclen(arg, '=');
		if (pos >= 0)
		{
			name = ft_strndup(arg, pos);
			value = ft_strcdup(arg, '\0', pos + 1);
		}
		if (pos == -1 && search_env(*env_v, name) == true)
			export_env(env_v, arg);
		else if (pos >= 0 && search_env(*env_v, name) == false)
			add_env(env_v, name, value, true);
		else if (pos >= 0 && search_env(*env_v, name) == true)
			rep_env(env_v, name, value, true);
	}
}
