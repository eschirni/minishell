/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 12:58:10 by eschirni          #+#    #+#             */
/*   Updated: 2022/03/01 20:39:22 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	free_arg(char **args, t_env_v *env_v)
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
	}
	free(args);
	return (atoi);
}

void	ft_exit(char **args, bool ctrl_d, t_env_v *env_v)
{
	if (ctrl_d == true)
	{
		rl_replace_line("", 0);
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
