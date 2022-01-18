/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:34:43 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/18 18:17:32 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_strchr(const char *s, int c)
{
	int	i;

	if (s == NULL)
		return (false);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (true);
		i++;
	}
	if (c == '\0')
		return (false);
	else
		return (false);
}
