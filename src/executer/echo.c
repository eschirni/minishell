/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:07:45 by tom               #+#    #+#             */
/*   Updated: 2022/02/16 13:14:09 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(char **input)
{
	bool	flag;
	int		i;
	int		j;

	j = 1;
	if (input[j] == NULL)
		return;
	flag = false;
	i = 0;
	if (input[j][i] == '-' && input[j][i + 1] == 'n' && input[j][i + 2] == '\0')
	{
		flag = true;
		j++;
	}
	while (input[j] != NULL)
	{
		i = 0;
		while (input[j][i] != '\0')
		{
			write(1, &input[j][i], 1);
			i++;
		}
		if (input[j + 1] != NULL)
			write(1, " ", 1);
		j++;
	}
	if (flag == false)
		write(1, "\n", 1);
}
