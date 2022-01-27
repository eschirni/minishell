/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 18:32:10 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/27 20:51:49 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd(void)
{
	char	*cwd;

	cwd = ft_calloc(138052520, 1); //138052520 because it's not too slow but handles still a really long pwd
	if (cwd == NULL)
		return ;
	getcwd(cwd, 138052520);
	if (cwd[0] =='\0')
	{
		ft_write_error(NULL, "pwd", "path too long");
		return ;
	}
	cwd = ft_append(cwd, "\n");
	write(1, cwd, ft_strclen(cwd, '\0'));
	free(cwd);
}
