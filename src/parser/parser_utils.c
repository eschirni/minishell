/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:03:06 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/17 21:45:20 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	in_quotes(char *s, int pos, char c)
{
	int	quotes;

	if (c == '\'' && in_quotes(s, pos, '"') == true)
		return (true);		
	quotes = 0;
	pos--;
	while (pos >= 0)
	{
		if (s[pos] == c)
			quotes++;
		pos--;
	}
	if (quotes % 2 == 0)
		return (false);
	return (true);
}

bool	check_quotes(char *s)
{
	if (in_quotes(s, ft_strclen(s, '\0'), '\'') == false)
		return (true);
	ft_write_error(NULL, NULL, "parse error");
	return (false);
}

static bool	remove_space(char *s, int i)
{
	if (s[i] != ' ' || (s[i] == ' ' && s[i + 1] != ' '))
		return (false);
	else if ((s[i] == ' ' && in_quotes(s, i, '\'') == true))
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

int	count_pipes(char *s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '|' && !in_quotes(s, i, '\''))
			count++;
		i++;
	}
	return (count);
}
