/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:43:44 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/03 22:05:18 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_word_size(char *s, int pos)
{
	int	size;

	size = 0;
	while (s[pos] != ' ' && s[pos] != '\0')
	{
		size++;
		pos++;
	}
	return (size);
}

char	*ft_replace_word(char *s, char *replace, int pos)
{
	char	*ret;
	int		size;
	int		i;
	int		j;

	i = 0;
	if (pos != 0)
	{
		ret = ft_strcdup(s, s[pos], 0);
		ret = ft_append(ret, replace);
		ret = ft_append(ret, &s[pos]);
	}
	else
	{
		ret = ft_strcdup(replace, '\0', 0);
		while (s[i] != ' ' && s[i] != '\0')
			i++;
		ret = ft_append(ret, &s[i]);
	}
	printf("%s\n", ret);
	// size = get_word_size(s, pos);
	// ret = malloc(ft_strclen(s, '\0') + ft_strclen(replace, '\0') - size + 1);
	// if (size < ft_strclen(replace, '\0'))
	// 	size = ft_strclen(replace, '\0');
	// i = 0;
	// j = 0;
	// while (s[i] != '\0' || size > 0)
	// {
	// 	if (i < pos || size == 0)
	// 		ret[i] = s[i];
	// 	else
	// 	{
	// 		ret[i] = replace[j];
	// 		j++;
	// 		size--;
	// 	}
	// 	i++;
	// }
	// ret[i] = '\0';
	//free(s);
	return (ret);
}
