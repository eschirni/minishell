/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:09:22 by eschirni          #+#    #+#             */
/*   Updated: 2022/03/01 20:57:11 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_home(char *ret, size_t *j)
{
	char	*home;
	size_t	i;

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
	size_t	i;
	size_t	j;
	char	*ret;

	ret = malloc(ft_strclen(path, '\0') + ft_strclen(getenv("HOME"), '\0'));
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (path[i] != '\0')
	{
		if (path[i] != '~')
			ret[j] = path[i];
		else
			set_home(ret, &j);
		i++;
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

static int	oldpwd(void)
{
	int		ret;
	char	*path;

	path = getenv("OLDPWD");
	if (path == NULL)
	{
		ft_write_error(NULL, "cd", "OLDPWD not set");
		return (-1);
	}
	write(1, path, ft_strclen(path, '\0'));
	write(1, "\n", 1);
	ret = chdir(path);
	return (ret);
}

void	cd(char *path, t_env_v *env_v)
{
	int		ret;
	char	*home;

	if (path == NULL)
		return ;
	if (ft_strchr(path, '~') == -1 && ft_strcmp(path, "-") != 0)
		ret = chdir(path);
	else if (ft_strcmp(path, "-") == 0)
		ret = oldpwd();
	else
	{
		home = replace_home(path);
		ret = chdir(home);
		free(home);
	}
	if (ret == -1)
	{
		if (ft_strcmp(path, "-") != 0)
			ft_write_error("cd", path, strerror(errno));
		rep_env(&env_v, ft_strdup("?"), ft_strdup("1"), false);
	}
	else
		rep_env(&env_v, ft_strdup("?"), ft_strdup("0"), false);
}
