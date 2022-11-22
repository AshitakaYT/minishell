/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 09:18:25 by aucousin          #+#    #+#             */
/*   Updated: 2022/10/15 16:53:41 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	ft_infile(t_process *proc)
{
	proc->file_in = open(proc->infile, O_RDONLY);
	if (proc->file_in == -1)
	{
		exit_perror(proc->infile, 1);
	}
	if (dup2(proc->file_in, STDIN_FILENO) < 0)
		perror("Fork: ");
	close(proc->file_in);
}

void	ft_outfile(t_process *proc)
{
	if (proc->append == 0)
		proc->file_out = open(proc->outfile, O_WRONLY);
	else
		proc->file_out = open(proc->outfile, O_WRONLY | O_APPEND);
	if (proc->file_out < 0)
		perror("Open: ");
	if (dup2(proc->file_out, STDOUT_FILENO) < 0)
		perror("Fork: ");
}

void	ft_hd2(t_process *proc)
{
	if (dup2(proc->heredocfd, STDIN_FILENO) < 0)
		perror("Fork: ");
	close(proc->heredocfd);
}

void	msh_execute_process(t_minishell *msh, t_process *proc)
{
	if (msh_isbuiltin(proc->cmd[0]))
	{
		if (msh_execbuiltin(proc, msh) == -1)
			exit (127);
	}
	else
	{
		msh_execbuiltout(msh, proc);
	}
	exit (0);
}

void	msh_execbuiltout(t_minishell *msh,
				t_process *proc)
{
	char	*cmd;
	int		i;

	i = 0;
	g_exit = INEXECVE;
	if (access(proc->cmd[0], F_OK) == 0)
		execve(proc->cmd[0], proc->cmd, msh->envp);
	while (msh->paths[i])
	{
		cmd = ft_strjoin(msh->paths[i], proc->cmd[0]);
		if (!cmd)
			exit (127);
		if (access(cmd, F_OK) == 0)
			execve(cmd, proc->cmd, msh->envp);
		free(cmd);
		i++;
	}
	write(2, "minish: command not found: ", 26);
	write(2, proc->cmd[0], ft_strlen(proc->cmd[0]));
	write(2, "\n", 1);
	exit (127);
}