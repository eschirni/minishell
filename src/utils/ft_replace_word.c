/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:43:44 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/07 19:36:24 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_replace_word(char *s, char *replace, int pos)
{
	char	*ret;

	if (replace == NULL)
		replace = "\0";
	if (pos != 0)
	{
		ret = ft_strndup(s, pos);
		ret = ft_append(ret, replace);
		while (s[pos] != ' ' && s[pos] != '\0')
			pos++;
		if (s[pos] != '\0')
			ret = ft_append(ret, &s[pos]);
	}
	else
	{
		ret = ft_strcdup(replace, '\0', 0);
		while (s[pos] != ' ' && s[pos] != '\0')
			pos++;
		ret = ft_append(ret, &s[pos]);
	}
	return (ret);
}
