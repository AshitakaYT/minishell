/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 02:20:45 by aucousin          #+#    #+#             */
/*   Updated: 2022/10/15 16:44:52 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	ft_child_status(int child_status)
{
	int	return_val;

	if (WIFEXITED(child_status) != 0)
		return_val = WEXITSTATUS(child_status);
	else
	{
		if (WIFSIGNALED(child_status) != 0)
			return_val = WTERMSIG(child_status) + 128;
		else
			return (0);
	}
	return (return_val);
}

void	ft_close_pipes(t_process *proc)
{
	while (proc->prev)
	{
		proc = proc->prev;
	}
	while (proc)
	{
		close(proc->end[0]);
		close(proc->end[1]);
		proc = proc->next;
	}
}

int	ft_create_pipes3(t_minishell *msh)
{
	t_process	*l;
	int			result;

	l = msh->process;
	while (l)
	{
		result = pipe(l->end);
		if (result < 0)
		{
			write(2, "minish: msh_execute: pipe failed.\n", 34);
			return (-1);
		}
		l = l->next;
	}
	return (0);
}

int	ft_create_forks3(t_minishell *msh)
{
	t_process	*l;

	l = msh->process;
	while (l)
	{
		l->child = fork();
		if (l->child < 0)
		{
			write(2, "minish: msh_execute: fork failed.\n", 34);
			return (-1);
		}
		else if (l->child == 0)
		{
			msh_child_process2(msh, l);
			ft_close_pipes(l);
			return (0);
		}
		l = l->next;
	}
	return (0);
}	

int	msh_execute(t_minishell *msh)
{
	t_process	*l;
	int			status;

	l = msh->process;
	g_exit = 0;
	if (!l->next && msh_isbuiltin(l->cmd[0]))
		return (msh_execbuiltin(l, msh));
	else
	{
		if (ft_create_pipes3(msh) == -1)
			return (-1);
		if (ft_create_forks3(msh) == -1)
			return (-1);
		ft_close_pipes(l);
		while (l)
		{
			waitpid(l->child, &status, 0);
			g_exit = ft_child_status(status);
			l = l->next;
		}
	}
	return (1);
}
