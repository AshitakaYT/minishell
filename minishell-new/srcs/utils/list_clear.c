/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:38:01 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/27 11:43:32 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	ft_tokensclear(t_token **lst)
{
	t_token	*l;
	t_token	*next;

	l = *lst;
	*lst = NULL;
	while (l)
	{
		if (l->str)
		{
			free(l->str);
			l->str = NULL;
		}
		next = l->next;
		free(l);
		l = next;
	}
	return ;
}

void	ft_redirsclear(t_redir **lst)
{
	t_redir	*l;
	t_redir	*next;

	l = *lst;
	*lst = NULL;
	while (l)
	{
		if (l->heredoc)
		{
			free(l->heredoc);
			l->heredoc = NULL;
		}
		if (l->file)
		{
			free(l->file);
			l->file = NULL;
		}
		next = l->next;
		free(l);
		l = next;
	}
	return ;
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void	ft_processclear(t_process **lst)
{
	t_process	*l;
	t_process	*next;

	l = *lst;
	*lst = NULL;
	while (l)
	{
		if (l->cmd)
			ft_free_tab(l->cmd);
		if (l->redirs)
			ft_redirsclear(&l->redirs);
		if (l->infile)
		{
			free(l->infile);
			l->infile = NULL;
		}
		if (l->outfile)
		{
			free(l->outfile);
			l->outfile = NULL;
		}
		next = l->next;
		free(l);
		l = next;
	}
}

void	ft_varclear(t_var *var)
{
	if (var->cmd)
	{
		free(var->cmd);
		var->cmd = NULL;
	}
	if (var->tmp)
	{
		free(var->tmp);
		var->tmp = NULL;
	}
	if (var->var)
	{
		free(var->var);
		var->var = NULL;
	}
}
