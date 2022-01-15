/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:08:49 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/15 14:09:10 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	*ft_calloc(size_t size)
{
	char	*c;

	c = malloc(size + 1);
	if (c == NULL)
		return (NULL);
	while (size + 1 != 0)
	{
		c[size] = '\0';
		size--;
	}
	return (c);
}
