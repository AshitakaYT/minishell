/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:48:43 by aucousin          #+#    #+#             */
/*   Updated: 2022/10/15 16:54:54 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	ft_middlecall(t_minishell *msh, t_process *proc)
{
	if (proc->heredoc)
		ft_hd2(proc);
	else if (proc->infile)
		ft_infile(proc);
	else if (dup2(proc->end[0], 0) < 0)
		perror("Fork: ");
	if (dup2(proc->next->end[1], 1) < 0)
		perror("Fork: ");
	ft_close_pipes(proc);
	msh_execute_process(msh, proc);
}

void	ft_firstcall(t_minishell *msh, t_process *proc)
{
	if (proc->heredoc)
		ft_hd2(proc);
	else if (proc->infile)
		ft_infile(proc);
	if (proc->outfile)
		ft_outfile(proc);
	else if (dup2(proc->next->end[1], STDOUT_FILENO) < 0)
		perror("Fork: ");
	ft_close_pipes(proc);
	msh_execute_process(msh, proc);
}

void	ft_lastcall(t_minishell *msh, t_process *proc)
{
	if (proc->heredoc)
		ft_hd2(proc);
	else if (proc->infile)
		ft_infile(proc);
	else if (dup2(proc->end[0], 0) < 0)
		perror("Fork: ");
	if (proc->outfile)
		ft_outfile(proc);
	ft_close_pipes(proc);
	msh_execute_process(msh, proc);
}

void	ft_onlycall(t_minishell *msh, t_process *proc)
{
	if (proc->heredoc)
		ft_hd2(proc);
	else if (proc->infile)
		ft_infile(proc);
	if (proc->outfile)
		ft_outfile(proc);
	msh_execute_process(msh, proc);
}

void	msh_child_process2(t_minishell *msh, t_process *proc)
{
	if (!proc->piped && proc->next)
		ft_firstcall(msh, proc);
	else if (proc->piped && proc->next)
		ft_middlecall(msh, proc);
	else if (proc->piped && !proc->next)
		ft_lastcall(msh, proc);
	else if (!proc->piped && !proc->next)
		ft_onlycall(msh, proc);
	ft_close_pipes(proc);
}
