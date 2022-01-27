/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:58:10 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/27 17:45:32 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	free_arg(char **args)
{
	int	i;
	int	atoi;

	i = 0;
	atoi = 0;
	if (args != NULL && args[1] != NULL)
		atoi = ft_atoi(args[1]);
	while (args != NULL && args[i] != NULL)
	{
		free(args[i]);
		i++;
		if (args[i] == NULL)
			free(args);
	}
	return (atoi);
}

void	ft_exit(char **args, bool ctrl_d, t_env *env)
{
	free_env(&env);
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
		exit(free_arg(args));
	}
	exit(free_arg(args));
}
