/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 04:47:40 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/23 22:40:59 by eschirni         ###   ########.fr       */
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

static bool	is_grep(char *s, int pos)
{
	pos--;
	if (pos < 2 || in_quotes(s, pos, '"', '\'') == true)
		return (false);
	if (s[pos] == 'e' && s[pos - 1] == 'r' && s[pos - 2] == 'g')
		return (true);
	return (false);
}

char	*replace_grep(char *s)
{
	char	*ret;
	char	*tmp;
	int		i;

	i = 0;
	ret = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == 'p' && is_grep(s, i) == true)
		{
			tmp = ft_strndup(s, i - 3);
			ret = ft_replace_word(&s[i], "grep -a");
			ret = ft_insert(tmp, ret);
			free(tmp);
		}
		i++;
	}
	if (ret == NULL)
		return (s);
	free(s);
	return (ret);
}
