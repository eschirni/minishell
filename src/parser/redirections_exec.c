/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:31:33 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/23 17:13:45 by eschirni         ###   ########.fr       */
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
