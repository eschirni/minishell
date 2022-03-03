/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 21:02:39 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/26 21:17:38 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_redirections(t_token *tokens, int type, int type1)
{
	int		i;
	t_token	*tmp;

	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type == type || tmp->type == type1)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

static void	make_heredoc(t_token *tmp, int *arr, int i)
{
	char	*heredoc;
	int		fd;

	heredoc = exec_heredoc(tmp->next->value);
	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	write (fd, heredoc, ft_strclen(heredoc, '\0'));
	close(fd);
	free(heredoc);
	arr[i] = redirections("heredoc", HEREDOC);
}

bool	safe_redirections(t_token *tokens, int type, int type1, int *arr)
{
	int		i;
	t_token	*tmp;

	tmp = tokens;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->type == type || tmp->type == type1)
		{
			if (tmp->type == HEREDOC)
				make_heredoc(tmp, arr, i);
			else
				arr[i] = redirections(tmp->next->value, tmp->type);
			if (arr[i] == -1)
				return (false);
			i++;
		}
		tmp = tmp->next;
	}
	arr[i] = -1;
	return (true);
}

int	**create_array(t_token *tokens)
{
	int		**arr;
	int		i;
	bool	no_error;

	arr = ft_calloc(2, sizeof(int *));
	if (arr == NULL)
		return (NULL);
	i = count_redirections(tokens, INPUT, HEREDOC);
	arr[0] = ft_calloc(i + 1, sizeof(int));
	i = count_redirections(tokens, TRUNC, APPEND);
	arr[1] = ft_calloc(i + 1, sizeof(int));
	if (arr[0] == NULL || arr[1] == NULL)
		return (NULL);
	no_error = safe_redirections(tokens, INPUT, HEREDOC, arr[0]);
	if (no_error == true)
		no_error = safe_redirections(tokens, TRUNC, APPEND, arr[1]);
	if (no_error == false)
	{
		free(arr[0]);
		free(arr[1]);
		free(arr);
		return (NULL);
	}
	return (arr);
}
