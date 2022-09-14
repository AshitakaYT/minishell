/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:29:28 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/14 18:53:32 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

char	**msh_realloc_env(t_minishell *msh, char *str)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (ft_tablen(msh->envp) + 2));
	while (i < ft_tablen(msh->envp))
	{
		new[i] = ft_strdup(msh->envp[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	i++;
	new[i] = 0;
	ft_free_tab(msh->envp);
	msh->envp = new;
	return (new);
}

int	msh_isintab(char **tab, char *str)
{
	int	i;
	int	j;

	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] && str[j] && tab[i][j] == str[j] && tab[i][j] != '=')
		{
			j++;
			if ((!tab[i][j] && !str[j])
			|| (tab[i][j] == '=' && (str[j] == '=' || !str[j])))
				return (i);
		}
		i++;
	}
	return (-1);
}

void	msh_update_env(t_minishell *msh, char *cmd, int i)
{
	free(msh->envp[i]);
	msh->envp[i] = ft_strdup(cmd);
}

void	msh_export_args(t_process *proc, t_minishell *msh)
{
	int	i;

	i = 1;
	while (proc->cmd[i])
	{
		if (msh_isintab(msh->envp, proc->cmd[i]) == -1)
		{
			printf("cmd[i] == %s\n, i == %d\n", proc->cmd[i], i);
			msh_realloc_env(msh, proc->cmd[i]);
		}
		else if (msh_isintab(msh->envp, proc->cmd[i]))
		{
			msh_update_env(msh, proc->cmd[i],
				msh_isintab(msh->envp, proc->cmd[i]));
		}
		i++;
	}
}

void	msh_export(t_process *proc, t_minishell *msh)
{
	if (!proc->cmd[1])
	{
		msh_export_noargs(msh);
	}
	else
	{
		msh_export_args(proc, msh);
	}
}
