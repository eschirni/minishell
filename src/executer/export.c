/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:58:13 by tom               #+#    #+#             */
/*   Updated: 2022/01/26 14:28:50 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export(t_env **env, char *argument)
{
	int		pos;
	char	*name;
	char	*value;

	pos = ft_strchr(argument, '=');
	if (pos >= 0)
	{
		name = ft_strndup(argument, pos);
		value = ft_strndup(&argument[pos + 1], ft_strlen(argument));
	}
	if (ft_strlen(argument) == 0)
		print_export(*env);
	else if (pos == -1 && search_env(*env, name) == true)
		export_env(env, argument);
	else if (pos >= 0 && search_env(*env, name) == false)
		add_env(env, name, value,true);
	else if (pos >= 0 && search_env(*env, name) == true)
		rep_env(env, name, value, true);
}