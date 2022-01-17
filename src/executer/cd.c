/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:09:22 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/18 00:30:50 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <errno.h>
#include <string.h>

void	cd(char *path) //check if I even have access
{
	char	*home;
	int		ret;
	char	*error;

	if (ft_strcmp(path, "~") == 0) //correct it so it works also for ~ in a string
	{
		home = getenv("HOME");
		path = home;
	}
	ret = chdir(path);
	if (ret == -1)
	{
		error = strerror(errno);
		write(2, error, ft_strclen(error, '\0'));
	}
}