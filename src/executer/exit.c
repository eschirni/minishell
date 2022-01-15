/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 20:42:42 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/15 14:44:57 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char *arg) //needs whatever comes after exit and spaces (allocated!!)
{
	int	exit_code;

	write(1, "exit\n", 5);
	if (arg[0] >= '9' || arg[0] <= '0')
	{
		arg = ft_insert("minishell: exit: ", arg);
		arg = ft_append(arg, ": numeric argument required\n");
		write(1, arg, ft_strclen(arg, '\0'));
	}
	exit_code = ft_atoi(arg);
	free(arg);
	exit(exit_code); //with what val does it exit when non numeric argument?
}
