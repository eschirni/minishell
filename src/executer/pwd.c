/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 21:28:38 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/15 14:18:10 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

void	pwd(void)
{
	char	*cwd;

	cwd = calloc(256, sizeof(char));
	if (getcwd(cwd, 256) == NULL)
		perror("pwd error");
	else
	{
		cwd = ft_append(cwd, "\n");
		write(1, cwd, 256);
	}
	free(cwd);
}
