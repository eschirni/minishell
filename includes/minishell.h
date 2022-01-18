/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:07:39 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/18 18:14:44 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h> //history_add
# include <readline/readline.h> //readline
# include <unistd.h> //write
# include <stdlib.h> //malloc, free
# include <signal.h> //signal, sigaction
# include <errno.h> //errno
# include <string.h> //strrerror
# include <stdbool.h> //bools
# include <limits.h>

typedef	struct		s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}					t_env;

//utils
void	*ft_calloc(size_t count, size_t size);
char	*ft_append(char *start, char *end);
char	*ft_insert(char *start, char *end);
size_t	ft_strclen(const char *s, char c);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(const char *s, char c);
bool	ft_strchr(const char *s, int c);
void	ft_write_error(char *command, char *arg, char *error);

void	executer(char **envp, char **commands);
void	cd(char *path);

#endif
