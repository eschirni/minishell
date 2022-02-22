/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 12:38:32 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/21 13:04:09 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*inner_string(int pos, t_token *tokens)
{
	char	*ret;
	int		i;
	t_token	*tmp;

	i = 1;
	tmp = tokens->next;
	ret = ft_strdup(tokens->value);
	while (i < pos)
	{
		ret = ft_append(ret, tmp->value);
		tmp = tmp->next;
		i++;
	}
	return (ret);
}

static int	ft_count_string(t_token *tokens, char c, int type)
{
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 1;
	while (tmp != NULL)
	{
		if (tmp->value == &c && type == tmp->type)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**ft_split_tokens(t_token *tokens, char c, int type)
{
	t_token	*tmp;
	char	**split;
	int		size;
	int		i;

	size = ft_count_string(tokens, c, type);
	split = malloc(size + 1);
	split[size] = NULL;
	i = 0;
	tmp = tokens;
	while (tmp != NULL)
	{
		if (tmp->value == &c && type == tmp->type)
		{
			split[i] = inner_string(i, tokens);
			i++;
		}
		tmp = tmp->next;
	}
	return (split);
}