/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 14:08:49 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/18 16:34:46 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*c;
	int		len;

	len = count * size;
	c = malloc(len);
	if (c == NULL)
		return (NULL);
	while (len > 0)
	{
		c[len - 1] = 0;
		len--;
	}
	return (c);
}
