/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 20:30:25 by tom               #+#    #+#             */
/*   Updated: 2022/02/26 20:51:37 by eschirni         ###   ########.fr       */
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

static void	iterate_split(char **ret, t_token *tokens)
{
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			tmp = tmp->next;
		ret[i] = ft_strdup(tmp->value);
		tmp = tmp->next;
		while (tmp != NULL && tmp->type != PIPE)
		{
			ret[i] = ft_append(ret[i], " ");
			ret[i] = ft_append(ret[i], tmp->value);
			tmp = tmp->next;
		}
		i++;
	}
	ret[i] = NULL;
}

char	**split_tokens(t_token *tokens)
{
	char	**ret;
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 1;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
		{
			i++;
			tmp = tmp->next;
		}
		tmp = tmp->next;
	}
	ret = ft_calloc(i + 1, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	iterate_split(ret, tokens);
	return (ret);
}
