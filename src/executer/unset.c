/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 01:39:46 by tom               #+#    #+#             */
/*   Updated: 2022/02/15 20:46:10 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	del_env(t_env **env, char *name)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	if (tmp != NULL && ft_strcmp(tmp->name, name) == 0)
	{
		*env = tmp->next; // Changed head
		free(tmp->name);
		free(tmp->value);
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
	free(tmp->name);
	free(tmp->value);
	free(tmp); // Free memory
}

void	unset(t_env **env_v, char *arg)
{
	char	*name;
	
	name = arg;
	if (ft_strcmp(name, "$?") == 0)
		return ;
	if (search_env(*env_v, name) == true)
		del_env(env_v, name);
}
