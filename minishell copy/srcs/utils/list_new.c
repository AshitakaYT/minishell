/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 06:55:47 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/07 16:01:10 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

t_token	*ft_tokennew(char *str, int type, int linked)
{
	t_token	*list;

	list = malloc(sizeof(t_token));
	if (!list)
		return (NULL);
	list->next = NULL;
	list->str = str;
	list->type = type;
	list->islinked = linked;
	return (list);
}

t_redir	*ft_redirnew(char *heredoc, int type, char *file)
{
	t_redir	*list;

	list = malloc(sizeof(t_redir));
	if (!list)
		return (NULL);
	list->next = NULL;
	list->type = type;
	list->file = ft_strdup(file);
	list->heredoc = heredoc;
	return (list);
}

t_process	*ft_processnew(char **cmd, int piped, t_process *prev)
{
	t_process	*list;

	list = malloc(sizeof(t_process));
	if (!list)
		return (NULL);
	list->next = NULL;
	list->redirs = NULL;
	list->cmd = cmd;
	list->infile = NULL;
	list->outfile = NULL;
	list->file_in = 0;
	list->file_out = 0;
	list->heredoc = 0;
	list->heredocs = 0;
	list->piped = piped;
	list->prev = prev;
	return (list);
}
