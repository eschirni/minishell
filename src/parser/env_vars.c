/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:58:59 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/11 21:15:54 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*translate(char *s, t_env *env_v)
{
	char	*var;
	char	*ret;
	int		i;

	i = 0;
	while (s[i] != ' ' && s[i] != '\0')
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
	return(ret);
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

static char	*replace_env_vars(char *s, t_env *env_v)
{
	char	*ret;

	ret = NULL;
	if (s [1] != '\0' && s[1] != ' ')
	{
		// if (in_quotes(s, i) == true)
		// 	return (s);
		ret = translate(s, env_v);
	}
	if (ret == NULL)
		return (s);
	free(s);
	return (ret);
}

char	*split_env_vars(char *s, t_env *env_v)
{
	char	**split;
	char	*ret;
	int		i;

	if (ft_strchr(s, '$') != 0)
		return (s);
	split = ft_split(s, '$');
	if (split == NULL) 
		return (s);
	i = 0;
	while(split[i] != NULL)
	{
		split[i] = replace_env_vars(split[i], env_v);
		i++;
	}
	i = 1;
	ret = ft_strdup(split[0]);
	while(split[i] != NULL)
	{
		ret = ft_append(ret, split[i]);
		i++;
	}
	ft_free_split(split);
	return(ret);
}
