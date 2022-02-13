/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:58:10 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/13 18:50:26 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	free_arg(char **args, t_env *env_v)
{
	int	i;
	int	atoi;

	free_env(&env_v);
	i = 0;
	atoi = 0;
	if (args != NULL && args[1] != NULL)
		atoi = ft_atoi(args[1]);
	while (args != NULL && args[i] != NULL)
	{
		free(args[i]);
		i++;
		// if (args[i] == NULL) makes no sense bro, malloc error on tom pc
		// 	free(args);
	}
	//system("leaks minishell");
	return (atoi);
}

void	ft_exit(char **args, bool ctrl_d, t_env *env_v)
{
	if(ctrl_d == true)
	{
		printf("\33[1A");
		rl_on_new_line();
		rl_redisplay();
	}
	write(1, "exit\n", 5);
	rl_clear_history();
	if (args != NULL && args[1] != NULL)
	{
		if (ft_isnum(args[1]) == false)
			ft_write_error("exit", args[1], "numeric argument required");
		else if (args[2] != NULL)
		{
			ft_write_error(NULL, "exit", "too many arguments");
			return ;
		}
		exit(free_arg(args, env_v));
	}
	exit(free_arg(args, env_v));
}
