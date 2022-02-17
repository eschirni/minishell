/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_exec.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 13:31:33 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/17 14:59:39 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	execute(char **split, char **envp, t_env *env_v, int i)
{
	int		fd;
	int		j;
	char	**tmp;

	PRINT_HERE();
	j = 0;
	while (j < i)
	{
		printf("%s\n", split[j]);
		j++;
	}
	fd = redirections(split[i - 1], split[i + 1], split[i]);
	tmp = malloc(i * sizeof(char *));
	j = 0;
	while (j < i)
	{
		tmp[j] = ft_strdup(split[j]);
		j++;
	}
	tmp[j] = NULL;
	PRINT_HERE();
	executer(envp, tmp, env_v);
	ft_free_split(tmp);
	reset_fd(fd, "<");
}

static bool	check_red(char **split, int i)
{
	if (ft_strcmp(split[i], "<") == 0 || ft_strcmp(split[i], ">") == 0)
		return (true);
	else if (ft_strcmp(split[i], "<<") == 0 || ft_strcmp(split[i], ">>") == 0)
		return (true);
	return (false);
}

void	exec_redirections(char **split, char **envp, t_env *env_v)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
	{
		if (check_red(split, i) == true)
			execute(split, envp, env_v, i);
		i++;
	}
}

int	count_redirections(char *s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '>' || s[i] == '<')
			count++;
		i++;
	}
	return (count);
}
