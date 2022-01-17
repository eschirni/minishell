/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:07:39 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/18 00:13:55 by eschirni         ###   ########.fr       */
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

//utils
void	*ft_calloc(size_t count, size_t size);
char	*ft_append(char *start, char *end);
char	*ft_insert(char *start, char *end);
size_t	ft_strclen(const char *s, char c);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(const char *s, char c);

void	executer(char **envp, char **commands);
void	cd(char *path);

#endif
