/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 11:07:45 by tom               #+#    #+#             */
/*   Updated: 2022/02/01 21:23:23 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	echo(char *input)
{
	bool	flag;
	int		i;

	if (input == NULL)
		return;
	flag = false;
	i = 0;
	if (input[i] == '-' && input[i + 1] == 'n' && input[i + 2] == ' ')
	{
		flag = true;
		i += 3;
	}
	printf("%s", &input[i]);
	if (flag == false)
		write(1, "\n", 1);
}
