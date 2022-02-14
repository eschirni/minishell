/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 17:54:34 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/14 19:15:54 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_name(char c)
{
	if (c > 32 && c < 127)
	{
		if (c != '|' && c != '>' && c != '<')
			return (true);
		return (false);
	}
	return (false);
}

bool	check_pipes(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '|')
		{
			i++;
			while (s[i] == ' ')
				i++;
			if (s[i] == '<' && s[i + 1] == '<')
				i += 2;
			else if (s[i] == '>' && s[i + 1] == '>')
				i += 2;
			else if(s[i] == '<' || s[i] == '>')
				i++;
			while (s[i] == ' ')
				i++;
			if (is_name(s[i]) == true)
				continue ;
			return (false);
		}
		i++;
	}
	return (true);
}
