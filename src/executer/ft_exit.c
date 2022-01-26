/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:58:10 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/26 14:30:23 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit(char **args, bool ctrl_d)
{
	if(ctrl_d == true)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	write(1, "exit\n", 5);
	if (args != NULL && args[1] != NULL)
	{
		if (ft_isnum(args[1]) == false)
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
