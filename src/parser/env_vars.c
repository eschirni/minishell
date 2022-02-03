/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 19:58:59 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/03 20:43:27 by eschirni         ###   ########.fr       */
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

static void	translate(char *s, int pos, t_env *env_v)
{
	char	*var;
	// t_env	*tmp;

	// tmp = env_v;
	// while (tmp != NULL)
	// {
		
	// 	tmp = tmp->next;
	// }
	var = get_var(s, pos);
	printf("%s\n", var);
	free(var);
}

static bool	in_quotes(char *s, int pos)
{
	int	quotes;
	int	i;

	quotes = 0;
	i = 0;
	while (i < pos)
	{
		if (s[i] == 39) //test with replacing into '\'' later
			quotes++;
		i++;
	}
	if (quotes % 2 == 0)
		return (false);
	return (true);
}

void	replace_env_vars(char *s, t_env *env_v)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '$' && s[i + 1] != '\0')
		{
			if (in_quotes(s, i) == true)
				return ;
			translate(s, i + 1, env_v);
			i++;
		}
		i++;
	}
}
