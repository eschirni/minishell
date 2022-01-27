/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:58:13 by tom               #+#    #+#             */
/*   Updated: 2022/01/27 23:00:16 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	*sort_env(t_env *env_v)
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

static void	print_export(t_env *env_v)
{
	t_env	*tmp;

	tmp = env_v;
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
		print_export(*env_v);
	else
	{
		pos = ft_strclen(arg, '=');
		if (pos >= 0)
		{
			name = ft_strcdup(arg, '=', 0);
			value = ft_strcdup(arg, '\0', pos + 1);
		}
		printf("%s\n%s\n", name, value);
		// if (pos == -1 && search_env(*env_v, name) == true)
		// 	export_env(env_v, arg);
		// else if (pos >= 0 && search_env(*env_v, name) == false)
		// 	add_env(env_v, name, value,true);
		// else if (pos >= 0 && search_env(*env_v, name) == true)
		// 	rep_env(env_v, name, value, true);
	}
}
