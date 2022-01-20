/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 16:41:43 by tom               #+#    #+#             */
/*   Updated: 2022/01/20 16:45:58 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	i;
	size_t	l;

	l = ft_strlen(s1) + 1;
	i = 0;
	p = malloc(sizeof(char) * l);
	if (p == NULL)
		return (NULL);
	while (i < l)
	{
		p[i] = s1[i];
		i++;
	}
	return (p);
}