/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:03:06 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/26 19:56:47 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	in_quotes(char *s, int pos, char quote, char other)
{
	int	count;
	int	count_other;
	int	i;

	if (quote == '"' && in_quotes(s, pos, '\'', '"') == true)
		return (true);
	count = 0;
	count_other = 0;
	i = 0;
	while (i < pos)
	{
		if (s[i] == other && count % 2 == 0)
			count_other++;
		else if (s[i] == quote && count_other % 2 == 0)
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (false);
	return (true);
}

bool	check_quotes(char *s)
{
	if (in_quotes(s, ft_strclen(s, '\0'), '"', '\'') == false)
		return (true);
	ft_write_error(NULL, NULL, "parse error");
	return (false);
}

static bool	remove_space(char *s, int i)
{
	if (s[i] != ' ' || (i > 0 && s[i] == ' ' && s[i - 1] != ' '))
		return (false);
	else if ((s[i] == ' ' && in_quotes(s, i, '"', '\'') == true))
		return (false);
	return (true);
}

char	*remove_spaces(char *s)
{
	int		i;
	int		size;
	char	*ret;

	i = 0;
	size = 0;
	while (s[i] != '\0')
	{
		if (remove_space(s, i) == false)
			size++;
		i++;
	}
	ret = malloc(size + 1);
	ret[size] = '\0';
	while (i >= 0)
	{
		if (remove_space(s, i) == false)
		{
			ret[size] = s[i];
			size--;
		}
		i--;
	}
	free(s);
	return (ret);
}

char	**convert_tokens(t_token *tokens)
{
	char	**ret;
	t_token	*tmp;
	int		i;

	tmp = tokens;
	i = 0;
	while (tmp != NULL && tmp->type == NONE)
	{
		tmp = tmp->next;
		i++;
	}
	ret = ft_calloc(i + 1, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	tmp = tokens;
	i = 0;
	while (tmp != NULL && tmp->type == NONE)
	{
		ret[i] = ft_strdup(tmp->value);
		tmp = tmp->next;
		i++;
	}
	ret[i] = NULL;
	return (ret);
}
