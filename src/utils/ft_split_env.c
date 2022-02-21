/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 10:56:42 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/21 12:14:22 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_create_array(size_t start, const char *s, size_t chars)
{
	char	*dst;
	size_t	i;

	i = 0;
	dst = malloc(chars + 1);
	while (i < chars)
	{
		dst[i] = s[start];
		start += 1;
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

static char	*ft_inner_string(size_t *start, const char *s, char c)
{
	size_t	chars;
	size_t	i;
	char	*dst;

	chars = 0;
	while (*start < ft_strclen(s, '\0'))
	{
		if (s[*start] != c)
		{
			i = *start;
			while (i < ft_strclen(s, '\0') && s[i] != c)
			{
				chars++;
				i++;
			}
			break ;
		}
		*start += 1;
	}
	dst = ft_create_array(*start, s, chars);
	*start += chars + 1;
	return (dst);
}

static int	ft_count_string(const char *s, char c)
{
	size_t	i;
	int		string_count;

	i = 0;
	string_count = 0;
	while (i < ft_strclen(s, '\0'))
	{
		if (s[i] != c)
		{
			string_count++;
			while (i < ft_strclen(s, '\0') && s[i] != c)
				i++;
			if (s[i] != '\0' && s[i + 1] == c)
				i++;
		}
		i++;
	}
	return (string_count);
}

char	**ft_split_env(const char *s, char c)
{
	int		string_count;
	size_t	i;
	size_t	start;
	char	**split;

	if (s == NULL)
		return (NULL);
	string_count = ft_count_string(s, c);
	if (string_count == 0)
		return (NULL);
	split = ft_calloc(string_count + 1, sizeof(char *));
	if (split == NULL)
		return (NULL);
	i = 0;
	start = 0;
	while (i < (size_t) string_count)
	{
		split[i] = ft_inner_string(&start, s, c);
		i++;
	}
	split[i] = NULL;
	return (split);
}
