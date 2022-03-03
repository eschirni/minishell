/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_stuff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 04:47:40 by eschirni          #+#    #+#             */
/*   Updated: 2022/03/01 20:37:36 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_size(char *s, char c)
{
	int	i;
	int	size;

	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		if (c == ' ' && (s[i] == '\'' || s[i] == '"'))
			c = s[i];
		else if (s[i] == c)
			c = ' ';
		else
			size++;
		i++;
	}
	return (size);
}

static char	*replace_quotes(t_token *tmp, char c)
{
	int		i;
	int		pos;
	char	*ret;

	i = get_size(tmp->value, c);
	ret = malloc(i + 1 * sizeof(char));
	if (ret == NULL)
		return (NULL);
	i = 0;
	pos = 0;
	while (tmp->value[i] != '\0')
	{
		if (c == ' ' && (tmp->value[i] == '\'' || tmp->value[i] == '"'))
			c = tmp->value[i];
		else if (tmp->value[i] == c)
			c = ' ';
		else
		{
			ret[pos] = tmp->value[i];
			pos++;
		}
		i++;
	}
	ret[pos] = '\0';
	return (ret);
}

void	remove_quotes(t_token *tokens)
{
	t_token	*tmp;
	char	c;

	tmp = tokens;
	while (tmp != NULL)
	{
		c = tmp->value[0];
		if ((c == '\'' || c == '"') && ft_strclen(tmp->value, '\0') >= 2)
		{
			free(tmp->value);
			tmp->value = replace_quotes(tmp, ' ');
		}
		tmp = tmp->next;
	}
}
