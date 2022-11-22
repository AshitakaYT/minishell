/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:11:00 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/28 16:43:15 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

char	**msh_realloc_env2(t_minishell *msh, int index)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (ft_tablen(msh->envp)));
	if (!new)
		return (NULL);
	while (i < ft_tablen(msh->envp) && i < index)
	{
		new[i] = ft_strdup(msh->envp[i]);
		if (!new[i])
			return (NULL);
		i++;
	}
	i++;
	while (i < ft_tablen(msh->envp))
	{
		new[i - 1] = ft_strdup(msh->envp[i]);
		if (!new[i - 1])
			return (NULL);
		i++;
	}
	new[i - 1] = 0;
	ft_free_tab(msh->envp);
	return (new);
}

int	ft_checkunsetarg(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
		{
			write (2, "minishell: msh_unset: ", 22);
			write (2, str, ft_strlen(str));
			write (2, ": not a valid identifier.\n", 26);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	msh_unset(t_process *proc, t_minishell *msh)
{
	int	i;

	i = 0;
	while (proc->cmd[i])
	{
		if (ft_checkunsetarg(proc->cmd[i]) == -1)
		{
			g_exit = 1;
			return (-1);
		}
		if (msh_isintab(msh->envp, proc->cmd[i]) != -1)
		{
			msh->envp = msh_realloc_env2(msh,
					msh_isintab(msh->envp, proc->cmd[i]));
			if (!msh->envp)
			{
				write (2, "minishell: msh_unset: malloc failed.\n", 38);
				g_exit = 1;
				return (-1);
			}
		}
		i++;
	}
	return (0);
}
