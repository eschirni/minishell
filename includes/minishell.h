/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:07:39 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/28 19:03:19 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //for readline??
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
	bool			export;
	struct s_env	*next;
}					t_env;

typedef	struct		s_lex
{
	char			*category;
	char			*value;
	struct s_lex	*next;
}					t_lex;

//utils
void	*ft_calloc(size_t count, size_t size);
char	*ft_append(char *start, char *end);
char	*ft_insert(char *start, char *end);
size_t	ft_strclen(const char *s, char c);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	**ft_split(const char *s, char c);
int		ft_strchr(const char *s, int c);
void	ft_write_error(char *command, char *arg, char *error);
char	*ft_strdup(const char *s1);
bool	ft_isnum(char *s);
void	ft_free_split(char **s);
char	*ft_strcdup(char *s, char c, int start);
char	*ft_strndup(const char *s1, int n);
void	ft_lstadd_back(t_env **env, t_env *new);

//executer
void	executer(char **envp, char **commands, t_env *env);
void	cd(char *path);
void	pwd(void);
void	ft_exit(char **args, bool ctrl_d, t_env *env);
void	env(t_env *env, char *argument);
void	export(t_env **env, char *arg);

//env handler
void	init_env(t_env **env, char **envp);
char	*get_value(t_env *env, char *name);
void	free_env(t_env **env);
t_env	*new_node(void);
bool	search_env(t_env *env, char *name);

//env utils
void	add_env(t_env **env, char *name, char *value, bool export);
void	rep_env(t_env **env, char *name, char *value, bool export);

#endif
