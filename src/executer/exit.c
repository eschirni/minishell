/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:42:42 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/15 14:27:24 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char *arg) //needs whatever comes after exit and spaces
{
	write(1, "exit\n", 5);
	if (arg[0] >= '9' || arg[0] <= '0')
		write(1, "numeric argument required\n", 26);
	exit(ft_atoi(arg)); //with what val does it exit when non numeric argument?
}
