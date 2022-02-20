/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 19:28:20 by tom               #+#    #+#             */
/*   Updated: 2022/02/20 19:30:06 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tmp != NULL)
	{
		tmp = tokens->next;
		free(tokens);
		tokens = tmp;
	}
}