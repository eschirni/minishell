/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 23:14:37 by tom               #+#    #+#             */
/*   Updated: 2022/02/25 17:18:56 by tom              ###   ########.fr       */
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
# define BLUE "\033[38;5;36m"
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define RESETCOLOR "\033[0m"

typedef struct s_command
{
	char				*cmd;
	char				*arguments;
	bool				redirection;
	pid_t				fd;
	struct s_command	*next;
}						t_command;

typedef struct s_cmd_table
{
	int				count;
	struct s_cmd	*command;
}					t_cmd_table;

typedef struct s_env
{
	char			*name;
	char			*value;
	bool			export;
	struct s_env	*next;
}					t_env;

typedef enum e_token_type{
	NONE,
	ARG,
	TRUNC,
	INPUT,
	APPEND,
	PIPE,
	HEREDOC
}			t_token_type;

typedef struct s_token
{
	int				index;
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}				t_token;

//utils
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strchr(const char *s, int c);
int		ft_isalnum(int c);
void	*ft_calloc(size_t count, size_t size);
void	ft_write_error(char *command, char *arg, char *error);
void	ft_free_split(char **s);
void	ft_lstadd_back(t_env **env_v, t_env *new);
void	ft_free_tokens(t_token *tokens);
char	*ft_append(char *start, char *end);
char	*ft_insert(char *start, char *end);
char	**ft_split(char *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strcdup(char *s, char c, int start);
char	*ft_strndup(const char *s1, int n);
char	*ft_replace_word(char *s, char *replace);
char	*ft_itoa(int n);
char	**ft_split_env(const char *s, char c);
char	**ft_split_tokens(t_token *tokens, int type);
bool	ft_isnum(char *s);
size_t	ft_strclen(const char *s, char c);

//executer
void	executer(char **envp, char **commands, t_env *env_v);
void	cd(char *path, t_env *env_v);
void	pwd(t_env *env_v);
void	ft_exit(char **args, bool ctrl_d, t_env *env_v);
void	env(t_env *env_v, char *argument);
void	export(t_env *env_v, char *arg);
void	unset(t_env **env_v, char *arg);
void	echo(char **input, t_env *env_v);

//env handler
void	init_env(t_env **env_v, char **envp);
void	free_env(t_env **env_v);
char	*get_value(t_env *env_v, char *name);
bool	search_env(t_env *env_v, char *name);
t_env	*new_node(void);

//env utils
void	add_env(t_env **env_v, char *name, char *value, bool export);
void	rep_env(t_env **env_v, char *name, char *value, bool export);

//parser
bool	has_redirections(t_token *tokens);
int		redirections(char *right, int type);
void	parser(char *line, char **envp, t_env *env_v);
void	ft_pipe(char **input, int pipe_count, char **envp, t_env *env_v);
void	reset_fd(int og_fd, char *operator);
char	*replace_grep(char *s);
void	remove_quotes(t_token *tokens);
char	*env_vars(char *s, t_env *env_v);
char	*exec_heredoc(char *delimiter);
char	*remove_spaces(char *s);
char	**convert_tokens(t_token *tokens);
bool	check_quotes(char *s);
bool	check_redirections(char *s);
bool	in_quotes(char *s, int pos, char c, char c2);
t_token	*lexer(char **line);

#endif
