/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:07:39 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/15 21:06:39 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdlib.h>
# include "get_next_line.h"

//utils
void	*ft_calloc(size_t size);
char	*ft_append(char *start, char *end);
char	*ft_insert(char *start, char *end);
size_t	ft_strclen(const char *s, char c);
int		ft_atoi(const char *str);

void	executer(char **envp, char ***commands);

void	ft_exit(char *arg);

#endif
