/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 19:08:40 by tom               #+#    #+#             */
/*   Updated: 2022/01/26 14:12:44 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strndup(const char *s1, int n)
{
	char	*p;
	size_t	i;

	i = 0;
	p = malloc(sizeof(char) * n);
	if (p == NULL)
		return (NULL);
	while (i < n && s1[i] != '\0')
	{
		p[i] = s1[i];
		i++;
	}
	return (p);
}