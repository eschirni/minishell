/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:23:10 by tom               #+#    #+#             */
/*   Updated: 2022/02/24 18:17:02 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*exec_heredoc(char *delimiter)
{
	char	*input;
	char	*tmp;

	input = malloc(1);
	if (input == NULL)
		return (NULL);
	while (1)
	{
		tmp = readline("heredoc> ");
		if (ft_strcmp(tmp, delimiter) == 0)
			break ;
		tmp = ft_append(tmp, "\n");
		input = ft_append(input, tmp);
		free(tmp);
	}
	return (input);
}
