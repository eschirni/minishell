/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 16:29:36 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/15 22:34:45 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	add_env(t_env **env_v, char *name, char *value, bool export)
{
	t_env	*new;

	new = new_node();
	new->name = name;
	new->value = value;
	new->export = export;
	ft_lstadd_back(env_v, new);
}

void	rep_env(t_env **env_v, char *name, char *value, bool export)
{
	t_env	*tmp;

	tmp = *env_v;
	if (tmp != NULL && ft_strcmp(tmp->name, name) == 0)
	{
		free(tmp->value);
		tmp->value = value;
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
	free(name);
	tmp->value = value;
	tmp->export = export;
}
