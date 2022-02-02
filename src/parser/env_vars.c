/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:58:59 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/02 21:59:58 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool	translate(char *s, int pos, t_env *env_v)
{
	t_env	*tmp;

	tmp = env_v;
	while (tmp != NULL)
	{
		
		tmp = tmp->next;
	}
}

static bool	in_quotes(char *s, int pos)
{
	int	quotes;
	int	i;

	quotes = 0;
	i = 0;
	while (i < pos)
	{
		if (s[i] == 39)
			quotes++;
		i++;
	}
	if (quotes % 2 == 0)
		return (false);
	return (true);
}

void	replace_env_vars(char *s, t_env *env_v)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '$')
		{
			if (in_quotes(s, i) == true)
				return ;
			
		}	
		i++;
	}
}
