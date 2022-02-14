/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:58:13 by tom               #+#    #+#             */
/*   Updated: 2022/02/14 16:52:19 by eschirni         ###   ########.fr       */
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

static t_env	*biggest_name(t_env *env_v)
{
	t_env	*tmp;
	t_env	*ret;

	ret = NULL;
	tmp = env_v;
	while (tmp != NULL)
	{
		if (ret == NULL)
			ret = tmp;
		else if (strcmp(tmp->name, ret->name) > 0)
			ret = tmp;
		tmp = tmp->next;
	}
	return (ret);
}

static char	*sort_env(t_env *env_v, char *last)
{
	t_env	*tmp;
	t_env	*low;
	int		i;

	tmp = env_v;
	low = biggest_name(env_v);
	while (tmp != NULL)
	{
		if (strcmp(low->name, tmp->name) > 0)
		{
			if (last == NULL || strcmp(tmp->name, last) > 0)
				low = tmp;
		}
		tmp = tmp->next;
	}
	if (low->export == true)
		printf("declare -x %s=\"%s\"\n", low->name, low->value);
	return (low->name);
}

static void	print_export(t_env *env_v)
{
	t_env	*tmp;
	char	*last;

	last = NULL;
	tmp = env_v;
	while (tmp != NULL)
	{
		last = sort_env(env_v, last);
		tmp = tmp->next;
	}
}

void	export(t_env *env_v, char *arg)
{
	int		pos;
	char	*name;
	char	*value;

	if (arg == NULL)
		print_export(env_v);
	else
	{
		pos = ft_strclen(arg, '=');
		if (pos == 0)
        {
            ft_write_error("export", arg, "not a valid identifier");
            return ;
		}
		else if (pos >= 0)
		{
			name = ft_strndup(arg, pos);
			value = ft_strcdup(arg, '\0', pos + 1);
		}
		if (pos == -1 && search_env(env_v, name) == true)
			export_env(&env_v, arg);
		else if (pos >= 0 && search_env(env_v, name) == false)
			add_env(&env_v, name, value, true);
		else if (pos >= 0 && search_env(env_v, name) == true)
			rep_env(&env_v, name, value, true);
	}
}
