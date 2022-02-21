/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 04:47:40 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/21 12:34:16 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	remove_quotes(t_token *tokens)
{
	t_token	*tmp;
	char	*rep;
	int		i;

	tmp = tokens;
	while (tmp != NULL)
	{
		if (tmp->value[0] == '\'' || tmp->value[0] == '"')
		{
			if (ft_strclen(tmp->value, '\0') >= 2)
			{
				i = 0;
				rep = ft_calloc(ft_strclen(tmp->value, '\0') - 1, 1);
				while (tmp->value[i + 2] != '\0')
				{
					rep[i] = tmp->value[i + 1];
					i++;
				}
				rep[i] = '\0';
				free(tmp->value);
				tmp->value = rep;
			}
		}
		tmp = tmp->next;
	}
}

void	replace_grep(t_token *tokens)
{
	t_token	*tmp;
	char	*rep;

	tmp = tokens;
	while (tmp != NULL)
	{		
		if (ft_strcmp(tmp->value, "grep") == 0)
		{
			if (tmp->next != NULL && ft_strcmp(tmp->next->value, "grep") != 0)
			{
				rep = ft_replace_word(tmp->value, "grep -a");
				free(tmp->value);
				tmp->value = rep;
			}
		}
		tmp = tmp->next;
	}
}
