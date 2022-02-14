/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:53:03 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/14 16:17:12 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	size_t	i;

// 	i = 0;
// 	while (s1[i] != s2[i] && (!(s1[i] == '\0' || s2[i] == '\0')))
// 	{
// 		if (s1[i] != s2[i])
// 			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
// 		else if (s1[i] == '\0' || s2[i] == '\0')
// 			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
// 		i++;
// 	}
// 	if (s1[i] == s2[i])
// 		return ((unsigned char) 0);
// 	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
// }

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*b1;
	unsigned char	*b2;

	write(1, "", 1); // segfault for some reason when "export test", delete later
	b1 = (unsigned char *)s1;
	b2 = (unsigned char *)s2;
	while (*b1 == *b2 && *b1 != '\0')
	{
		b1++;
		b2++;
	}
	if (*b1 == *b2)
		return (0);
	else
		return (*b1 - *b2);
}
