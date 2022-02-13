/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:58:59 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/13 19:20:08 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*translate(char *s, t_env *env_v)
{
	char	*var;
	char	*ret;
	int		i;

	i = 0;
	while (s[i] != ' ' && s[i] != '\0' && s[i] != '\'' && s[i] != '"')
		i++;
	var = malloc(i + 1);
	if (var == NULL)
		return (NULL);
	var[i] = '\0';
	i--;
	while (i >= 0)
	{
		var[i] = s[i];
		i--;
	}
	ret = ft_replace_word(s, get_value(env_v, var));
	free(var);
	return (ret);
}

static bool	in_quotes(char **split, int pos)
{
	int	quotes;
	int	i;

	quotes = 0;
	pos--;
	while (pos >= 0)
	{
		i = 0;
		while (split[pos][i] != '\0')
		{
			if (split[pos][i] == '\'')
				quotes++;
			i++;
		}
		pos--;
	}
	if (quotes % 2 == 0)
		return (false);
	return (true);
}

static char	*replace_env_var(char **split, t_env *env_v, int pos)
{
	char	*ret;

	ret = NULL;

	if (split[pos][0] != ' ')
	{
		if (in_quotes(split, pos) == true)
		{
			split[pos] = ft_insert("$", split[pos]);
			return (split[pos]);
		}
		ret = translate(split[pos], env_v);
	}
	else
	{
		ret = ft_strdup(split[pos]);
		ret = ft_insert("$", ret);
	}
	free(split[pos]);
	return (ret);
}

static char	*split_env_vars(char *s, bool dol_at_end, t_env *env_v)
{
	char	*ret;
	char	**split;
	int		i;

	split = ft_split(s, '$');
	if (split == NULL)
		return (NULL);
	i = 1;
	if (s[0] == '$')
		i = 0;
	else
		ret = ft_strdup(split[0]);
	while (split[i] != NULL)
	{
		split[i] = replace_env_var(split, env_v, i);
		if (i == 0)
			ret = ft_strdup(split[0]);
		else
			ret = ft_append(ret, split[i]);
		i++;
	}
	if (dol_at_end == true)
		ret = ft_append(ret, "$");
	ft_free_split(split);
	return (ret);
}

char	*env_vars(char *s, t_env *env_v)
{
	bool	dol_at_end;
	char	*ret;
	int		len;

	if (ft_strchr(s, '$') < 0)
		return (s);
	dol_at_end = false;
	len = ft_strclen(s, '\0');
	if (len >= 2 && s[len - 1] == '$' && s[len - 2] != '$')
		dol_at_end = true;
	ret = split_env_vars(s, dol_at_end, env_v);
	if (ret == NULL)
		return (s);
	free(s);
	return (ret);
}
