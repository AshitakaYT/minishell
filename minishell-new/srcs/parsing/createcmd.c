/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createcmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:31:38 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/27 09:28:23 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

char	*ft_parsecmd(t_token *lst, t_minishell *msh)
{
	char	*cmd;

	cmd = NULL;
	if (lst->type == TEXT)
		cmd = ft_handletxt(lst, msh);
	else if (lst->type == SQTEXT)
		cmd = ft_handlesq(lst);
	else
		cmd = ft_handledq(lst, msh);
	if (!cmd)
		return (NULL);
	if (lst->islinked == 1)
	{
		cmd = ft_strjoin(cmd, ft_parsecmd(lst->next, msh));
		if (!cmd)
			return (NULL);
		lst = lst->next;
	}
	return (cmd);
}

char	**msh_create_cmd(t_token *lst, t_minishell *msh)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = malloc(sizeof (char *) * (msh_count_cmd(lst) + 1));
	if (!cmds)
		return (NULL);
	while (lst && lst->type != PIPE)
	{
		if (ft_isred(lst->type))
			lst = lst->next;
		else
		{
			cmds[i] = ft_parsecmd(lst, msh);
			if (!cmds[i++])
				return (ft_freetab_retnull(cmds));
			while (lst && lst->islinked)
				lst = lst->next;
		}
		lst = lst->next;
	}
	cmds[i] = NULL;
	return (cmds);
}
