/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_isbuiltin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 16:16:07 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/28 16:09:02 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	msh_isbuiltin(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "echo") == 0 \
		|| ft_strcmp(cmd, "env") == 0 || ft_strcmp(cmd, "exit") == 0 \
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0 \
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "$?") == 0)
		return (1);
	return (0);
}

int	msh_execbuiltin2(t_process *proc, t_minishell *msh)
{
	if (ft_strcmp(proc->cmd[0], "exit") == 0)
		msh_exit(proc, msh);
	else if (ft_strcmp(proc->cmd[0], "pwd") == 0)
		msh_pwd(proc, msh);
	else if (ft_strcmp(proc->cmd[0], "export") == 0)
	{
		if (msh_export(proc, msh) == -1)
		{
			write (2, "minishell: msh_export: malloc failed.\n", 38);
			g_exit = 1;
			return (-1);
		}
	}
	else if (ft_strcmp(proc->cmd[0], "unset") == 0)
	{
		if (msh_unset(proc, msh) == -1)
		{
			g_exit = 1;
			return (-1);
		}
	}
	return (0);
}

int	msh_execbuiltin(t_process *proc, t_minishell *msh)
{
	if (ft_strcmp(proc->cmd[0], "cd") == 0)
	{
		if (msh_cd(proc, msh) == -1)
		{
			g_exit = 1;
			return (-1);
		}
	}
	else if (ft_strcmp(proc->cmd[0], "echo") == 0)
		msh_echo(proc, msh);
	else if (ft_strcmp(proc->cmd[0], "env") == 0)
		msh_env(proc, msh);
	else
		return (msh_execbuiltin2(proc, msh));
	return (0);
}
