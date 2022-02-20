/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:32:10 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/19 15:37:54 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(t_env *env_v)
{
	char	*cwd;

	cwd = ft_calloc(18052520, 1); //18052520 because it's not too slow but handles still a really long pwd
	if (cwd == NULL)
		return ;
	getcwd(cwd, 18052520);
	if (cwd[0] == '\0')
	{
		ft_write_error(NULL, "pwd", "path too long");
		return ;
	}
	cwd = ft_append(cwd, "\n");
	write(1, cwd, ft_strclen(cwd, '\0'));
	free(cwd);
	rep_env(&env_v, ft_strdup("?"), ft_strdup("0"), false);
}
