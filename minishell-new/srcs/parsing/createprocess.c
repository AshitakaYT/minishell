/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createprocess.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:34:31 by aucousin          #+#    #+#             */
/*   Updated: 2022/10/14 19:04:52 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	msh_create_processinit(t_minishell *msh, t_token *lst, t_process **process)
{
	char		**cmd;

	if (!lst)
		return (-1);
	cmd = msh_create_cmd(lst, msh);
	if (!cmd)
		return (-1);
	*process = ft_processnew(cmd, 0, NULL);
	if (!*process)
	{
		ft_free_tab(cmd);
		return (-1);
	}
	ft_processadd_back(&msh->process, *process);
	return (0);
}

int	msh_whilenopipe(t_token **lst, t_process *process, t_minishell *msh)
{
	t_process	*tmp;

	tmp = process;
	process = ft_processnew(msh_create_cmd((*lst)->next, msh), 1, tmp);
	if (!process || !process->cmd)
		return (-1);
	(*lst) = (*lst)->next;
	ft_processadd_back(&msh->process, process);
	return (0);
}

int	msh_create_process(t_minishell *msh, t_token *lst)
{
	t_process	*process;
	t_redir		*redir;

	if (msh_create_processinit(msh, lst, &process) == -1)
		return (-1);
	while (lst)
	{
		while (lst && lst->type != PIPE)
		{
			if (ft_isred(lst->type))
			{
				redir = NULL;
				redir = ft_redirnew(NULL, lst->type, lst->next->str);
				if (!redir)
					return (-1);
				ft_redirprocaddback(&process, redir);
				lst = lst->next;
			}
			lst = lst->next;
		}
		if (lst)
			if (msh_whilenopipe(&lst, process, msh) == -1)
				return (-1);
	}
	return (0);
}
