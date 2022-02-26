/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 19:38:17 by eschirni          #+#    #+#             */
/*   Updated: 2022/02/26 19:59:35 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_name(char c)
{
	if (c > 32 && c < 127)
	{
		if (c != '|' && c != '>' && c != '<')
			return (true);
		return (false);
	}
	return (false);
}

static bool	check_pipes(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '|' && in_quotes(s, i, '"', '\'') == false)
		{
			i++;
			while (s[i] == ' ')
				i++;
			if (s[i] == '<' && s[i + 1] == '<')
				i += 2;
			else if (s[i] == '>' && s[i + 1] == '>')
				i += 2;
			else if (s[i] == '<' || s[i] == '>')
				i++;
			while (s[i] == ' ')
				i++;
			if (is_name(s[i]) == true)
				continue ;
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	check_arrows(char *s, char arrow)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (!in_quotes(s, i, '"', '\'') && s[i] == arrow && s[i + 1] != arrow)
		{
			i++;
			while (s[i] == ' ')
				i++;
			if (is_name(s[i]) == true)
				continue ;
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	check_double_arrows(char *s, char arrow)
{
	int	i;

	i = 0;
	while (s[i + 1] != '\0')
	{
		if (s[i] == arrow && s[i + 1] == arrow)
		{
			i += 2;
			while (s[i] == ' ')
				i++;
			if (is_name(s[i]) == true)
				continue ;
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_redirections(char *s)
{
	if (check_pipes(s) == false)
	{
		ft_write_error(NULL, NULL, "parse error");
		return (false);
	}
	if (check_arrows(s, '<') == false || check_arrows(s, '>') == false)
	{
		ft_write_error(NULL, NULL, "parse error");
		return (false);
	}
	if (check_double_arrows(s, '<') == false
		|| check_double_arrows(s, '>') == false)
	{
		ft_write_error(NULL, NULL, "parse error");
		return (false);
	}
	return (true);
}
