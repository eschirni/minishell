/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:42:42 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/14 22:05:43 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char *arg)
{
	write(1, "exit\n", 5);
	if (arg[0] >= '9' || arg[0] <= '0')
		write(1, "numeric argument required\n", 26);
	exit(0); //with what val does it exit when non numeric argument?
}
