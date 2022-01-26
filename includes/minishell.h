/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 17:07:39 by eschirni          #+#    #+#             */
/*   Updated: 2022/01/25 20:15:38 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <limits.h>

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
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
void	ft_lstadd_back(t_env **env, t_env *new);
int	ft_strchr(const char *s, int c);
char	*ft_strndup(const char *s1, int n);

void	executer(char **envp, char **commands);
void	init_env(t_env **env, char **envp);
void	print_env(t_env *env);
void	add_env(t_env **env, char *name, char *value, bool export);
void	del_env(t_env **env, char *name);
void	rep_env(t_env **env, char *name, char *value, bool export);
char	*get_value(t_env *env, char *name);
void	free_env(t_env **env);
void	print_export(t_env *env);
void	export_env(t_env **env, char *name);
bool	search_env(t_env *env, char *name);
void	export(t_env **env, char *argument);

#endif
