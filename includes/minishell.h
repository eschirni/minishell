/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:07:39 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/17 20:26:54 by eschirni         ###   ########.fr       */
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
# include <fcntl.h>	//open
# include <limits.h>

# define PRINT_HERE() (printf("in file: %s at line %d\n", __FILE__, __LINE__))

typedef	struct		s_env
{
	char			*name;
	char			*value;
	bool			export;
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
int		ft_strchr(const char *s, int c);
void	ft_write_error(char *command, char *arg, char *error);
char	*ft_strdup(const char *s1);
bool	ft_isnum(char *s);
void	ft_free_split(char **s);
char	*ft_strcdup(char *s, char c, int start);
char	*ft_strndup(const char *s1, int n);
void	ft_lstadd_back(t_env **env_v, t_env *new);
char	*ft_replace_word(char *s, char *replace);

//executer
void	executer(char **envp, char **commands, t_env *env_v);
void	cd(char *path);
void	pwd(void);
void	ft_exit(char **args, bool ctrl_d, t_env *env_v);
void	env(t_env *env_v, char *argument);
void	export(t_env *env_v, char *arg);
void	unset(t_env **env_v, char *arg);
void	echo(char **input);

//env handler
void	init_env(t_env **env_v, char **envp);
char	*get_value(t_env *env_v, char *name);
void	free_env(t_env **env_v);
t_env	*new_node(void);
bool	search_env(t_env *env_v, char *name);

//env utils
void	add_env(t_env **env_v, char *name, char *value, bool export);
void	rep_env(t_env **env_v, char *name, char *value, bool export);

//parser
void	parser(char *line, char **envp, t_env *env_v);
char	*env_vars(char *s, t_env *env_v);
bool	check_redirections(char *s);
int		count_pipes(char *s);
void	ft_pipe(char **input, int pipe_count, char **envp, t_env *env_v);
int		count_redirections(char *s);
int		redirections(char *left, char *right, char *operator);
void	reset_fd(int og_fd, char *operator);
void	exec_redirections(char **split, char **envp, t_env *env_v);
char	*remove_spaces(char *s);
bool	check_quotes(char *s);
bool	in_quotes(char *s, int pos, char c);

#endif
