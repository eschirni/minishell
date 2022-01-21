/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:58:10 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/21 14:17:38 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char *val)
{
	write(1, "exit\n", 5);
	if (val != NULL)
	{
		if (!(val[0] >= '0' && val[0] <= '9'))
			ft_write_error("exit", val, "numeric argument required");
		exit(ft_atoi(val));
	}
	exit(0);
}
