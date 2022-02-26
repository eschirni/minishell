/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:30:25 by tom               #+#    #+#             */
/*   Updated: 2022/02/26 20:41:56 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*after_pipe(t_token *tokens)
{
	t_token	*tmp;
	t_token	*end;

	end = tokens;
	while (end != NULL)
	{
		if (end->type == PIPE)
			tmp = end->next;
		end = end->next;
	}
	return (tmp);
}

char	**split_tokens(t_token *tokens, int type)
{
	char	**ret;
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 1;
	while (tmp != NULL)
	{
		if (tmp->type == type)
		{
			i++;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	ret = ft_calloc(i + 1, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type == type)
			tmp = tmp->next;
		ret[i] = ft_strdup(tmp->value);
		tmp = tmp->next;
		while (tmp != NULL && tmp->type != type)
		{
			ret[i] = ft_append(ret[i], " ");
			ret[i] = ft_append(ret[i], tmp->value);
			tmp = tmp->next;
		}
		i++;
	}
	ret[i] = NULL;
	return (ret);
}