/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:29:25 by tom               #+#    #+#             */
/*   Updated: 2022/02/19 14:42:50 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env(t_env *env_v, char *arg)
{
	t_env	*tmp;

	if (arg != NULL)
		return ;
	tmp = env_v;
	while (tmp != NULL)
	{
		if (tmp->export == true)
			printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	rep_env(&env_v, ft_strdup("?"), ft_strdup("0"), false);
}
