/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 02:20:45 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/15 15:05:09 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	ft_close_pipes(t_process *proc)
{
	while (proc)
	{
		close(proc->end[0]);
		close(proc->end[1]);
		proc = proc->prev;
	}
}

void	msh_execute_process(t_minishell *msh, t_process *proc)
{
	char	*cmd;
	int		i;

	i = 0;
	printf("%s\n", proc->cmd[0]);
	if (msh_isbuiltin(proc->cmd[0]))
	{
		printf("Builtin detected, opinion accepted.\n");
		msh_execbuiltin(proc, msh);
	}
	else
	{
		printf("Builtout detected, opinion rejected.\n");
		if (access(proc->cmd[0], F_OK) == 0)
			execve(proc->cmd[0], proc->cmd, msh->envp);
		while (msh->paths[i])
		{
			cmd = ft_strjoin(msh->paths[i], proc->cmd[0]);
			if (!cmd)
				exit(EXIT_FAILURE);
			if (access(cmd, F_OK) == 0)
				execve(cmd, proc->cmd, msh->envp);
			free(cmd);
			i++;
		}
		write(2, "pipex: command not found: ", 26);
		write(2, proc->cmd[0], ft_strlen(proc->cmd[0]));
		write(2, "\n", 1);
		exit (1);
	}
}

void	ft_infile(t_process *proc)
{
	proc->file_in = open(proc->infile, O_RDONLY);
	if (dup2(proc->file_in, STDIN_FILENO) < 0)
		perror("Fork: ");
	close(proc->file_in);
	printf("Go infile mon clasheuuuur\n");
}

void	ft_piped(t_process *proc)
{
	close(proc->prev->end[1]);
	if (dup2(proc->prev->end[0], STDIN_FILENO) < 0)
		perror("Fork: ");
}

void	ft_outfile(t_process *proc)
{
	proc->file_out = open(proc->outfile,
			O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (proc->file_out < 0)
		printf("get rekt\n");
	if (dup2(proc->file_out, STDOUT_FILENO) < 0)
		perror("Fork: ");
	//if (close(proc->file_out) < 0)
		printf("get rekt\n");
	printf("Go outfile mon clasheuuuur\n");
}

void	ft_hd(t_process *proc)
{
	t_redir	*l;
	int		i;

	i = 0;
	l = proc->redirs;
	while (i < proc->heredocs)
	{
		if (l->type == DLRED)
			i++;
		else
			l = l->next;
	}
	i = ft_strlen(l->heredoc);
	if (write(proc->end[1], l->heredoc, i) < 0)
	{
		perror("Cannot write to file.");
		exit(1);
	}
	close(proc->end[1]);
	if (dup2(proc->end[0], STDIN_FILENO) < 0)
		perror("Fork: ");
	printf("ratched\n");
}

void	ft_next(t_process *proc)
{
	close(proc->end[0]);
	if (dup2(proc->end[1], STDOUT_FILENO) < 0)
		perror("Fork: ");
	close(proc->end[1]);
	printf("Go next mon clasheuuuur\n");
}

void	msh_child_process(t_minishell *msh, t_process *proc)
{
	if (proc->heredoc)
		ft_hd(proc);
	else if (proc->infile)
		ft_infile(proc);
	else if (proc->piped)
		ft_piped(proc);
	if (proc->outfile)
		ft_outfile(proc);
	else if (proc->next)
		ft_next(proc);
	if (!proc->next)
		close(proc->end[1]);
	ft_close_pipes(proc);
	msh_execute_process(msh, proc);
	if (proc->infile)
		close(proc->file_in);
	if (proc->outfile)
		close(proc->file_out);
}

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

int	msh_execute(t_minishell *msh)
{
	t_process	*l;
//	t_process	*tmp;
	int			status;
	printf("g_exitinit = %d\n", g_exit);
	l = msh->process;
	if (!l->next && msh_isbuiltin(l->cmd[0]))
	{
		msh_execbuiltin(l, msh);
		return (1);
	}
	else
	{
		while (l)
		{
			pipe(l->end);
			l->child = fork();
			if (!l->child)
				msh_child_process(msh, l);
			l = l->next;
		}
		l = msh->process;
		while (l)
		{
			close(l->end[0]);
			close(l->end[1]);
			waitpid(l->child, &status, 0);
			g_exit = ft_child_status(status);
			printf("g_exit = %d\n", g_exit);
			l = l->next;
		}
		return (1);
	}
}
