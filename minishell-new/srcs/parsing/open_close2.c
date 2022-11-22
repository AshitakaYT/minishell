/*
int	open_process_files(t_process *pipex)
// WILL NEED ERROR MANAGEMENT
{
	t_redir	*l;

	l = pipex->redirs;
	while (l)
	{
		if (l->type == RRED || l->type == DRRED)
		{
			pipex->file_out = open(l->file,
					O_CREAT | O_WRONLY | O_TRUNC, 0777);
			if (pipex->file_out < 0)
			{
				perror(l->file);
				g_exit = 1;
				return (-1);
			}
			pipex->outfile = ft_strdup(l->file);
			if (!pipex->outfile)
				return (-1);
		}
		else if (l->type == LRED || l->type == DLRED)
		{
			if (l->type == LRED)
			{
				pipex->file_in = open(l->file, O_RDONLY);
				if (pipex->file_in < 0)
				{
					perror(l->file);
					g_exit = 127;
					return (-1);
				}
			}
			pipex->infile = ft_strdup(l->file);
			if (!pipex->infile)
				return (-1);
			pipex->piped = 0;
			if (l->type == DLRED)
			{
				pipex->heredoc = 1;
				pipex->heredocs++;
			}
			else
				pipex->heredoc = 0;
		}
		l = l->next;
	}
	return (1);
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

void	msh_child_process(t_minishell *msh, t_process *proc)
{
	if (proc->heredoc)
		ft_hd2(proc);
	else if (proc->infile)
		ft_infile(proc);
	else if (proc->piped)
		ft_piped(proc);
	if (proc->outfile)
		ft_outfile(proc);
	else if (proc->next)
		ft_next(proc);
	//if (!proc->next)
	//	close(proc->end[1]);
	msh_execute_process(msh, proc);
	ft_close_pipes(proc);
	//if (proc->infile)
	//	close(proc->file_in);
	//if (proc->outfile)
	//	close(proc->file_out);
}
*/