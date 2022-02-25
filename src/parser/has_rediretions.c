/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   has_rediretions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 21:14:38 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/25 21:15:38 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	has_redirections(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp != NULL)
	{
		if (tmp->type != NONE)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

bool	has_pipes(t_token *tokens)
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}
