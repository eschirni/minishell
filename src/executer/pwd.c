/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 21:28:38 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/14 21:43:35 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdio.h>

void	pwd(void)
{
	char	cwd[256];

	if (getcwd(cwd, 256) == NULL)
		perror("pwd error");
	else
		write(1, cwd, 256);
}
