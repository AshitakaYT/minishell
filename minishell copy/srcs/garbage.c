/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 07:03:15 by aucousin          #+#    #+#             */
/*   Updated: 2022/08/17 15:52:13 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

char	**msh_split_line(t_minishell *minishell)
// call with lines, 64, 0
{
	char	**tokens;
	char	*token;

	minishell->tokens = malloc(sizeof(char *) * buff_size);
	if (!tokens)
	{
		write(2, "allocution error.\n", 17);
		exit(EXIT_FAILURE);
	}
	token = ft_get_token(line, TOKEN_DELIMITERS);
	while (token)
	{
		tokens[pos] = token;
		pos++;
		if (pos >= buff_size)
		{
			buff_size += TOKEN_BUFFSIZE;
			tokens = ft_realloctab(tokens, buff_size);
			if (!tokens)
			{
				write(2, "allocution error.\n", 17);
				exit(EXIT_FAILURE);
			}
		}
	}
	tokens[pos] = NULL;
	return (tokens);
}

char	**msh_split_line(char *line, int buff_size, int pos)
// call with lines, 64, 0
{
	char	**tokens;
	char	*token;

	tokens = malloc(sizeof(char *) * buff_size);
	if (!tokens)
	{
		write(2, "allocution error.\n", 17);
		exit(EXIT_FAILURE);
	}
	token = ft_get_token(line, TOKEN_DELIMITERS);
	while (token)
	{
		tokens[pos] = token;
		pos++;
		if (pos >= buff_size)
		{
			buff_size += TOKEN_BUFFSIZE;
			tokens = ft_realloctab(tokens, buff_size);
			if (!tokens)
			{
				write(2, "allocution error.\n", 17);
				exit(EXIT_FAILURE);
			}
		}
	}
	tokens[pos] = NULL;
	return (tokens);
}

int		msh_count_tokens(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		while (line[i] && line[i] == ' ')
		{
			i++;
		}
		if (line[i] && ft_isredirection(line[i]))
		{
			if (line[i + 1 && line[i] == line[i + 1]])
				i++;
			count++;
			i++;
		}
		else if (line[i] && ft_isalnum(line[i]))
		{
			while (line[i] && ft_isalnum(line[i]))
			{
				i++;
			}
			count++;
		}
		else if (line[i] && line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
			{
				i++;
			}
			count++;
		}
		else if (line[i] && line[i] == 39)
		{
			i++;
			while (line[i] && line[i] != 39)
			{
				i++;
			}
			count++;
		}
	}
}

void	msh_child_process(t_minishell *msh, t_process *pipex)
{
	int		i;
	char	*cmd;

	if (pipex->infile && pipex->next && !pipex->outfile) // there is an infile and there is a next
	{
		if (dup2(pipex->file_in, STDIN_FILENO < 0))
			perror("Fork: ");
		if (dup2(pipex->end[1], STDOUT_FILENO) < 0)
			perror("Fork: ");
		close(pipex->next->end[0]);
	}
	else if (!pipex->piped && pipex->next && !pipex->outfile)
	{
		if (dup2(pipex->end[1], STDOUT_FILENO) < 0)
			perror("Fork: ");
	}
	else if (pipex->next && !pipex->outfile)
	{
		if (dup2(pipex->end[1], STDIN_FILENO < 0))
			perror("Fork: ");
		if (dup2(pipex->next->end[1], STDOUT_FILENO < 0))
			perror("Fork: ");
	}
	else if (!pipex->next || pipex->outfile)
	{
		if (dup2(pipex->end[0], STDIN_FILENO) < 0)
			perror("Fork: ");
		if (dup2(pipex->file_out, STDOUT_FILENO) < 0)
			perror("Fork: ");
	}
	close(pipex->end[1]);
	if (dup2(pipex->file_out, STDOUT_FILENO) < 0)
		perror("Fork: ");
	if (dup2(pipex->end[0], STDIN_FILENO) < 0)
		perror("Fork: ");
	close(pipex->file_out);
	
	else if (!pipex->piped && !pipex->next && !pipex->outfile)
	{
		(void);
	}




	
	if (dup2(pipex->end[1], STDIN_FILENO) < 0)
	close(pipex->next->end[0]);

	if (dup2(pipex->file_in, STDIN_FILENO < 0))
		perror("Fork: ");
	if (dup2(pipex->file_in, STDIN_FILENO) < 0)
		perror("Fork: ");
	dup2(pipex->end[1], STDOUT_FILENO);
	close(pipex->file_in);
	i = 0;
	while (msh->paths[i])
	{
		cmd = ft_strjoin(msh->paths[i], pipex->cmd[0]);
		if (!cmd)
			exit(EXIT_FAILURE);
		if (access(cmd, F_OK) == 0)
			execve(cmd, pipex->cmd, msh->envp);
		free(cmd);
		i++;
	}
	write(2, "pipex: command not found: ", 26);
	write(2, pipex->cmd[0], ft_strlen(pipex->cmd[0]));
	write(2, "\n", 1);
	exit (1);
}

void	child_one(t_pipex *pipex)
{
	int		i;
	char	*cmd;

	close(pipex->end[0]);
	if (dup2(pipex->file_in, STDIN_FILENO < 0))
		perror("Fork: ");
	if (dup2(pipex->end[1], STDOUT_FILENO) < 0)
		perror("Fork: ");
	dup2(pipex->end[1], STDOUT_FILENO);
	close(pipex->file_in);
	i = 0;
	while (pipex->paths[i])
	{
		cmd = ft_strjoin(pipex->paths[i], pipex->cmd1[0]);
		if (!cmd)
			exit(EXIT_FAILURE);
		if (access(cmd, F_OK) == 0)
			execve(cmd, pipex->cmd1, pipex->env);
		free(cmd);
		i++;
	}
	write(2, "pipex: command not found: ", 26);
	write(2, pipex->cmd1[0], ft_strlen(pipex->cmd1[0]));
	write(2, "\n", 1);
	exit (1);
}

void	child_two(t_pipex *pipex)
{
	int		i;
	char	*cmd;

	close(pipex->end[1]);
	if (dup2(pipex->file_out, STDOUT_FILENO) < 0)
		perror("Fork: ");
	if (dup2(pipex->end[0], STDIN_FILENO) < 0)
		perror("Fork: ");
	close(pipex->file_out);
	i = 0;
	while (pipex->paths[i])
	{
		cmd = ft_strjoin(pipex->paths[i], pipex->cmd2[0]);
		if (!cmd)
			exit(EXIT_FAILURE);
		if (access(cmd, F_OK) == 0)
			execve(cmd, pipex->cmd2, pipex->env);
		free(cmd);
		i++;
	}
	write(2, "pipex: command not found: ", 26);
	write(2, pipex->cmd2[0], ft_strlen(pipex->cmd2[0]));
	write(2, "\n", 1);
	exit (127);
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

void	ft_pipe(t_pipex *pipex)
{
	int		status;
	pid_t	child1;
	pid_t	child2;

	pipe(pipex->end);
	child1 = fork();
	if (child1 < 0)
		perror("Fork: ");
	if (!child1)
		child_one(pipex);
	child2 = fork();
	if (child2 < 0)
		perror("Fork: ");
	if (!child2)
		child_two(pipex);
	close(pipex->end[0]);
	close(pipex->end[1]);
	waitpid(child1, &status, 0);
	waitpid(child2, &status, 0);
	if (ft_child_status(status) != 0)
		exit (ft_child_status(status));
}
/*
void	ft_heredoc2(t_redir *heredoc)
{
	char	*tmp;

	heredoc->line = NULL;
	heredoc->heredoc = "\0";
	while (1)
	{
		printf("file = %s\n", heredoc->file);
		heredoc->line = NULL;
		tmp = NULL;
		write(1, "> ", 2);
		heredoc->line = readline(tmp);
		free(tmp);
		heredoc->tmp = heredoc->heredoc;
		write(heredoc->herepipe[1], heredoc->line, ft_strlen(heredoc->line));
		if (ft_strcmp(heredoc->file, heredoc->line) == 1)
		{
			printf("heredoc = %s\n", heredoc->heredoc);
			break ;
		}
		write(heredoc->herepipe[1], "\n", 1);
	}
}

int	heredoc_execute(t_redir *here)
{
	int	status;

	pipe(here->herepipe);
	here->herechild = fork();
	if (!here->herechild)
		ft_heredoc2(here);
	close(here->herepipe[1]);
	close(here->herepipe[2]);
	waitpid(here->herechild, &status, 0);
}


void	ft_heredocs(t_process *process)
{
	int			i;
	t_redir		*l;
	t_process	*p;

	i = 0;
	p = process;
	while (p)
	{
		l = p->redirs;
		while (l)
		{
			if (l->type == DLRED)
			{
				ft_heredoc(l);
			}
			l = l->next;
		}
		p = p->next;
	}
}
*/