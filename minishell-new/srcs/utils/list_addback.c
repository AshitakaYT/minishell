/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_addback.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:36:12 by aucousin          #+#    #+#             */
/*   Updated: 2022/10/14 19:05:12 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	ft_tokenadd_back(t_token **alst, t_token *new)
{
	if (!*alst)
		*alst = new;
	else if ((*alst)->next)
		ft_tokenadd_back(&(*alst)->next, new);
	else
		(*alst)->next = new;
}

void	ft_rediradd_back(t_redir **alst, t_redir *new)
{
	if (!*alst)
		*alst = new;
	else if ((*alst)->next)
		ft_rediradd_back(&(*alst)->next, new);
	else
		(*alst)->next = new;
}

void	ft_redirprocaddback(t_process **alst, t_redir *new)
{
	while ((*alst)->next)
	{
		*alst = (*alst)->next;
	}
	ft_rediradd_back(&(*alst)->redirs, new);
}

void	ft_processadd_back(t_process **alst, t_process *new)
{
	if (!*alst)
		*alst = new;
	else if ((*alst)->next)
		ft_processadd_back(&(*alst)->next, new);
	else
		(*alst)->next = new;
}
