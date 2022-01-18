/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 17:44:28 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/18 18:17:43 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_write_error(char *command, char *arg, char *error)
{
	write(2, "minishell: ", 11);
	write(2, command, ft_strclen(command, '\0'));
	write(2, ": ", 2);
	write(2, arg, ft_strclen(arg, '\0'));
	write(2, ": ", 2);
	write(2, error, ft_strclen(error, '\0'));
	write(2, "\n", 1);
}
