/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eschirni <eschirni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 14:02:37 by tom               #+#    #+#             */
/*   Updated: 2022/02/21 12:24:17 by eschirni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define RESETCOLOR "\033[0m"
#define GREEN "\033[0;32m"

t_token	*init_tokens(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->index = 0;
	new->value = NULL;
	new->next = NULL;
	new->type = NONE;
	return (new);
}

void	input_token_data(t_token *tokens, char **line, int i)
{
	if (ft_strcmp(line[i], "|") == 0)
	{
		tokens->type = PIPE;
		tokens->value = ft_strdup(line[i]);
	}
	else if (ft_strcmp(line[i], "<") == 0)
	{
		tokens->type = INPUT;
		tokens->value = ft_strdup(line[i]);
	}
	else if (ft_strcmp(line[i], ">") == 0)
	{
		tokens->type = TRUNC;
		tokens->value = ft_strdup(line[i]);
	}
	else if (ft_strcmp(line[i], ">>") == 0)
	{
		tokens->type = APPEND;
		tokens->value = ft_strdup(line[i]);
	}
	else if (ft_strcmp(line[i], "<<") == 0)
	{
		tokens->type = HEREDOC;
		tokens->value = ft_strdup(line[i]);
	}
}

static void	get_tokens(t_token *tokens, char **line)
{
	t_token	*new;
	int		i;

	i = 0;
	while (line[i] != NULL)
	{
		tokens->index = i;
		input_token_data(tokens, line, i);
		if (tokens->type == NONE)
			tokens->value = ft_strdup(line[i]);
		if (line[i + 1] != NULL)
		{
			new = init_tokens();
			tokens->next = new;
			tokens = tokens->next;
		}
		i++;
	}
}

t_token	*lexer(char **line)
{
	t_token	*tokens;

	if (line == NULL)
		return (NULL);
	tokens = NULL;
	tokens = init_tokens();
	get_tokens(tokens, line);
	ft_free_split(line);
	return (tokens);
}
