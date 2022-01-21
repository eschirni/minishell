/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:58:10 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/21 15:51:21 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char **args)
{
	write(1, "exit\n", 5);
	if (args[1] != NULL)
	{
		if (!(args[1][0] >= '0' && args[1][0] <= '9'))
			ft_write_error("exit", args[1], "numeric argument required");
		else if (args[2] != NULL)
		{
			ft_write_error(NULL, "exit", "too many arguments");
			return ;
		}
		exit(ft_atoi(args[1]));
	}
	exit(0);
}
