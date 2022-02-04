/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:58:59 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/04 17:54:49 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*get_var(char *s, int pos)
{
	char	*ret;
	int		size;

	size = 0;
	while (s[pos] != ' ' && s[pos] != '\0')
	{
		size++;
		pos++;
	}
	ret = malloc(size + 1);
	ret[size] = '\0';
	while (s[pos] != '$')
	{
		size--;
		pos--;
		ret[size] = s[pos];
	}
	return (ret);
}

static char	*translate(char *s, int pos, t_env *env_v)
{
	char	*var;
	char	*ret;

	var = get_var(s, pos + 1);
	s = ft_replace_word(s, get_value(env_v, var), pos);
	free(var);
	return(s);
}

static bool	in_quotes(char *s, int pos)
{
	int	quotes;
	int	i;

	quotes = 0;
	i = 0;
	while (i < pos)
	{
		if (s[i] == '\'')
			quotes++;
		i++;
	}
	if (quotes % 2 == 0)
		return (false);
	return (true);
}

char	*replace_env_vars(char *s, t_env *env_v)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	while (s[i] != '\0')
	{
		if (s[i] == '$' && s[i + 1] != '\0')
		{
			if (in_quotes(s, i) == true)
				return (s);
			if (ret == NULL)
				ret = translate(s, i, env_v);
			else
				ret = translate(ret, i, env_v);
			i++;
		}
		i++;
	}
	if (ret == NULL)
		return (s);
	free(s);
	return (ret);
}
