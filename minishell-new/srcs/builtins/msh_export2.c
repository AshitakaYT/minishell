/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:29:28 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/28 16:07:43 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

char	**msh_realloc_env(t_minishell *msh, char *str)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (ft_tablen(msh->envp) + 2));
	if (!new)
		return (NULL);
	while (i < ft_tablen(msh->envp))
	{
		new[i] = ft_strdup(msh->envp[i]);
		if (!new[i])
			return (NULL);
		i++;
	}
	new[i] = ft_strdup(str);
	if (!new[i])
		return (NULL);
	i++;
	new[i] = 0;
	ft_free_tab(msh->envp);
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

int	msh_update_env(t_minishell *msh, char *cmd, int i)
{
	free(msh->envp[i]);
	msh->envp[i] = NULL;
	msh->envp[i] = ft_strdup(cmd);
	if (!msh->envp[i])
		return (-1);
	return (0);
}

int	msh_export_args(t_process *proc, t_minishell *msh)
{
	int	i;

	i = 0;
	while (proc->cmd[++i])
	{
		if (verif_args_env(proc->cmd[i]) == -1)
		{
			write(2, "export: not valid in this context\n", 34);
			return (-1);
		}
		if (msh_isintab(msh->envp, proc->cmd[i]) == -1)
		{
			msh->envp = msh_realloc_env(msh, proc->cmd[i]);
			if (!msh->envp)
				return (-1);
		}
		else if (msh_isintab(msh->envp, proc->cmd[i]))
		{
			if (msh_update_env(msh, proc->cmd[i],
					msh_isintab(msh->envp, proc->cmd[i])) == -1)
				return (-1);
		}
	}
	ft_sort_string_tab(msh->envp);
	return (0);
}

int	msh_export(t_process *proc, t_minishell *msh)
{
	if (!proc->cmd[1])
	{
		msh_export_noargs(msh);
	}
	else
	{
		if (msh_export_args(proc, msh) == -1)
			return (-1);
	}
	return (0);
}
