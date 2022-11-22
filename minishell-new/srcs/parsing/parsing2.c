/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:04:59 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/27 11:43:26 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

t_token	*msh_get_tokens2(char *line, int *i, int linked)
{
	t_token	*token;

	token = NULL;
	if (line[(*i)] && ft_isprintsh(line[(*i)]) && !ft_isred(line[(*i)]))
		token = msh_parse_txt(line, &linked, i);
	else if (line[(*i)] && (line[(*i)]) == 39)
		token = msh_parse_sq(line, &linked, i);
	else if (line[(*i)] && (line[(*i)]) == '"')
		token = msh_parse_dbq(line, &linked, i);
	else if (line[(*i)] && ft_isred2(line[(*i)]))
		token = msh_parse_red(line, &linked, i);
	else if (line[(*i)] && (line[(*i)]) == '|')
		token = ft_tokennew(ft_strndup(&line[(*i)++], 1), PIPE, linked);
	return (token);
}

int	msh_get_tokens(t_minishell *msh, char *line)
{
	int		i;
	int		linked;
	t_token	*token;

	i = 0;
	linked = 0;
	if (!line || !line[0])
		return (-1);
	while (line[i] && line[i] != '\n')
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (!line[i])
			return (0);
		token = msh_get_tokens2(line, &i, linked);
		if (!token)
			return (-1);
		ft_tokenadd_back(&msh->tokens, token);
		token = NULL;
	}
	return (0);
}

int	msh_count_cmd(t_token *lst)
{
	int	i;

	i = 0;
	while (lst && lst->type != PIPE)
	{
		if (ft_isred(lst->type))
		{
			lst = lst->next;
		}
		else if (lst->islinked == 0)
			i++;
		lst = lst->next;
	}
	return (i);
}

int	msh_parse_redir(t_minishell *msh)
{
	t_process	*l;

	l = msh->process;
	while (l)
	{
		if (open_process_files(l) == -1)
			return (-1);
		l = l->next;
	}
	return (1);
}
