/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 06:55:47 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/27 09:52:47 by aucousin         ###   ########.fr       */
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
	list->str = ft_strdup(str);
	free(str);
	if (!list->str)
	{
		free(list);
		return (NULL);
	}
	list->type = type;
	list->islinked = linked;
	return (list);
}

t_redir	*ft_redirnew2(t_redir *list, char *heredoc)
{
	if (heredoc)
	{
		list->heredoc = ft_strdup(heredoc);
		if (!list->heredoc)
		{
			ft_redirsclear(&list);
			return (NULL);
		}
	}
	else
		list->heredoc = NULL;
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
	if (file)
	{
		list->file = ft_strdup(file);
		if (!list->file)
		{
			free(list);
			return (NULL);
		}
	}
	else
		list->file = NULL;
	return (ft_redirnew2(list, heredoc));
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
	list->append = 0;
	list->heredocs = 0;
	list->piped = piped;
	list->prev = prev;
	return (list);
}
