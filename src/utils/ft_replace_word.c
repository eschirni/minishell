/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 20:43:44 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/21 12:20:24 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_replace_word(char *s, char *replace)
{
	char	*ret;
	int		pos;

	if (replace == NULL)
		replace = "\0";
	ret = ft_strcdup(replace, '\0', 0);
	pos = 0;
	while (s[pos] != ' ' && s[pos] != '\0' && s[pos] != '\'' && s[pos] != '"')
		pos++;
	ret = ft_append(ret, &s[pos]);
	return (ret);
}
