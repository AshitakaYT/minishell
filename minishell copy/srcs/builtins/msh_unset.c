/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:11:00 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/09 08:37:15 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

char	**msh_realloc_env2(t_minishell *msh, int index)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (ft_tablen(msh->envp)));
	while (i < ft_tablen(msh->envp) && i < index)
	{
		new[i] = ft_strdup(msh->envp[i]);
		i++;
	}
	i++;
	while (i < ft_tablen(msh->envp))
	{
		new[i - 1] = ft_strdup(msh->envp[i]);
		i++;
	}
	new[i - 1] = 0;
	ft_free_tab(msh->envp);
	msh->envp = new;
	return (new);
}

void	msh_unset(t_process *proc, t_minishell *msh)
{
	int	i;
	int	j;

	i = 0;
	while (proc->cmd[i])
	{
		j = msh_isintab(msh->envp, proc->cmd[i]);
		if (msh_isintab(msh->envp, proc->cmd[i]))
		{
			msh_realloc_env2(msh,
				msh_isintab(msh->envp, proc->cmd[i]));
		}
		i++;
	}
}
