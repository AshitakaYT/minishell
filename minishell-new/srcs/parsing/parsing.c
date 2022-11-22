/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:20:25 by aucousin          #+#    #+#             */
/*   Updated: 2022/10/15 16:47:12 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	ft_checkred(t_token *list)
{
	if (!list)
		return (0);
	if (list->type == PIPE)
	{
		ft_dprintf(2, "bash: syntax error near token `%s'\n", list->str);
		return (0);
	}	
	while (list)
	{
		if ((ft_isred(list->type) && !list->next)
			|| (list->type == PIPE && !list->next))
		{
			ft_dprintf(2, "minish: syntax error near token `newline'\n");
			return (0);
		}
		else if ((ft_isred(list->type) && !ft_istxt(list->next->type))
			|| (list->type == PIPE && list->next->type == PIPE))
		{
			ft_dprintf(2, "bash: syntax error near token `%s'\n", list->str);
			return (0);
		}
		list = list->next;
	}
	return (1);
}

t_token	*msh_parse_txt(char *line, int *linked, int *i)
{
	t_token	*token;

	token = NULL;
	token = ft_tokennew(ft_strndup(&line[(*i)],
				ft_len_alnum(&line[(*i)])), TEXT, (*linked));
	if (!token)
		return (token);
	(*i) += ft_len_alnum(&line[(*i)]);
	if (line[(*i)] && (line[(*i)] == '"'
			|| line[(*i)] == 39 || ft_isalnum(line[(*i)])))
	{
		token->islinked = 1;
	}
	else
		(*linked) = 0;
	return (token);
}

t_token	*msh_parse_sq(char *line, int *linked, int *i)
{
	t_token	*token;

	token = NULL;
	if (ft_lenquote(&line[(*i)]) == -1)
	{
		ft_dprintf(2, "unvalid single quote.\n");
		return (NULL);
	}
	token = ft_tokennew(ft_strndup(&line[(*i)],
				ft_lenquote(&line[(*i)])), SQTEXT, (*linked));
	(*i) += ft_lenquote(&line[(*i)]);
	if (line[(*i)] && (line[(*i)] == '"'
			|| line[(*i)] == 39 || ft_isalnum(line[(*i)])))
		token->islinked = 1;
	else
		(*linked) = 0;
	return (token);
}

t_token	*msh_parse_dbq(char *line, int *linked, int *i)
{
	t_token	*token;

	token = NULL;
	if (ft_lendbquote(&line[(*i)]) == -1)
	{
		ft_dprintf(2, "unvalid double quote.\n");
		return (NULL);
	}
	token = ft_tokennew(ft_strndup(&line[(*i)],
				ft_lendbquote(&line[(*i)])), DQTEXT, (*linked));
	(*i) += ft_lendbquote(&line[(*i)]);
	if (line[(*i)] && (line[(*i)] == '"'
			|| line[(*i)] == 39 || ft_isalnum(line[(*i)])))
	{
		token->islinked = 1;
	}
	else
		(*linked) = 0;
	return (token);
}

t_token	*msh_parse_red(char *line, int *linked, int *i)
{
	t_token	*token;

	token = NULL;
	if (line[(*i)] && (line[(*i)]) == '>' && ((line[(*i) + 1]
				&& line[(*i) + 1] != '>') || !line[(*i) + 1]))
		token = ft_tokennew(ft_strndup(&line[(*i)++], 1), RRED, (*linked));
	else if (line[(*i)] && (line[(*i)]) == '>'
		&& line[(*i) + 1] && line[(*i) + 1] == '>')
	{
		token = ft_tokennew(ft_strndup(&line[(*i)], 2), DRRED, (*linked));
		(*i) += 2;
	}
	else if (line[(*i)] && (line[(*i)]) == '<'
		&& line[(*i) + 1] && line[(*i) + 1] == '<')
	{
		token = ft_tokennew(ft_strndup(&line[(*i)], 2), DLRED, (*linked));
		(*i) += 2;
	}
	else if (line[(*i)] && (line[(*i)]) == '<'
		&& ((line[(*i) + 1] && line[(*i) + 1] != '<') || !line[(*i) + 1]))
		token = ft_tokennew(ft_strndup(&line[(*i)++], 1), LRED, (*linked));
	else
		token = NULL;
	(*linked) = 0;
	return (token);
}
