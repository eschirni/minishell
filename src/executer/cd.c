/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:09:22 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/18 17:53:38 by eschirni         ###   ########.fr       */
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
	if (ret == NULL)
		return (NULL);
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
	return(ret);
}

void	cd(char *path)
{
	int		ret;
	char	*home;

	if (ft_strchr(path, '~') == false)
		ret = chdir(path);
	else
	{
		home = replace_home(path);
		ret = chdir(home);
		free(home);
	}
	if (ret == -1)
		ft_write_error("cd", path, strerror(errno));
}
