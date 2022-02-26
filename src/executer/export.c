/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:58:13 by tom               #+#    #+#             */
/*   Updated: 2022/02/26 21:16:02 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	export_env(t_env_v **env, char *name)
{
	t_env_v	*tmp;

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

static t_env_v	*biggest_name(t_env_v *env_v)
{
	t_env_v	*tmp;
	t_env_v	*ret;

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

static char	*sort_env(t_env_v *env_v, char *last)
{
	t_env_v	*tmp;
	t_env_v	*low;

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

static void	export_var(t_env_v *env_v, char *arg)
{
	int		pos;
	char	*name;
	char	*value;

	pos = ft_strclen(arg, '=');
	if (pos == 0 || arg[0] == '$')
	{
		ft_write_error("export", arg, "not a valid identifier");
		rep_env(&env_v, ft_strdup("?"), ft_strdup("1"), false);
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
	rep_env(&env_v, ft_strdup("?"), ft_strdup("0"), false);
}

void	export(t_env_v *env_v, char *arg)
{
	t_env_v	*tmp;
	char	*last;

	if (arg == NULL)
	{
		last = NULL;
		tmp = env_v;
		while (tmp != NULL)
		{
			last = sort_env(env_v, last);
			tmp = tmp->next;
		}
		rep_env(&env_v, ft_strdup("?"), ft_strdup("0"), false);
	}
	else
		export_var(env_v, arg);
}
