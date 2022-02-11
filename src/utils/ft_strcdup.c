/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 22:49:15 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/11 21:09:21 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strcdup(char *s, char c, int start)
{
	char	*ret;
	int		i;

	ret = ft_calloc(ft_strclen(s, c) - start + 1, 1);
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (s[start] != c)
	{
		ret[i] = s[start];
		start ++;
		i++;
	}
	ret[i] = s[start];
	ret[i + 1] = '\0';
	return (ret);
}
