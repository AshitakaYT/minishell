/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:38:01 by aucousin          #+#    #+#             */
/*   Updated: 2022/06/07 22:06:02 by aucousin         ###   ########lyon.fr   */
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
			free(l->str);
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
		i++;
	}
	free(tab);
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
		next = l->next;
		free(l);
		l = next;
	}
	return ;
}
