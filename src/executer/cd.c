/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:09:22 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/18 16:35:29 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_home(char *ret, int	*j)
{
	char	*home;
	int		i;

	home = getenv("HOME");
	i = 0;
	while (home[i] != '\0')
	{
		ret[*j] = home[i];
		*j += 1;
		i++;
	}
	*j -= 1;
}

static char	*replace_home(char *path)
{
	int		i;
	int		j;
	char	*ret;

	ret = malloc(ft_strclen(path, '\0') + ft_strclen(getenv("HOME"), '\0'));
	//protect malloc
	i = 0;
	j = 0;
	while(path[i] != '\0')
	{
		if (path[i] != '~')
			ret[j] = path[i];
		else
			set_home(ret, &j);
		i++;
		j++;
	}
	ret[j] = '\0';
	//free(path);
	return(ret);
}

void	cd(char *path) //check if I even have access
{
	char	*home;
	int		ret;
	char	*error;

	if (ft_strcmp(path, "~") == 0) //correct it so it works also for ~ in a string
		path = replace_home(path);
	ret = chdir(path);
	if (ret == -1)
	{
		error = strerror(errno);
		write(2, error, ft_strclen(error, '\0'));
	}
	free(path);
}