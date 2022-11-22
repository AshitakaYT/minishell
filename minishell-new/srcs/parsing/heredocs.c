/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:13:38 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/27 11:43:08 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	fork_hd(int *pipe, t_redir *heredoc)
{
	int		i;
	char	*tmp;

	i = 1;
	g_exit = INHEREDOC_FORK;
	close(pipe[0]);
	while (i != 0)
	{
		tmp = readline("> ");
		if (tmp == NULL)
			break ;
		i = ft_strcmp(heredoc->file, tmp);
		if (i != 0)
		{
			ft_putstr_fd(tmp, pipe[1]);
			ft_putstr_fd("\n", pipe[1]);
			free(tmp);
			tmp = NULL;
		}
	}
	close(pipe[1]);
	exit(0);
}

int	ft_heredoc(t_process *process, t_redir *heredoc)
{
	int		fd;
	int		pipex[2];
	int		status;
	int		result;

	result = pipe(pipex);
	if (result < 0)
	{
		write(2, "minish: ft_heredoc: pipe failed.\n", 34);
		return (-1);
	}
	fd = fork();
	g_exit = INHEREDOC;
	if (fd == 0)
		fork_hd(pipex, heredoc);
	close(pipex[1]);
	wait(&status);
	g_exit = ft_child_status(status);
	process->heredocfd = pipex[0];
	return (0);
}

int	ft_heredocs(t_process *process)
{
	t_redir		*l;
	t_process	*p;

	p = process;
	while (p)
	{
		l = p->redirs;
		while (l)
		{
			if (l->type == DLRED)
			{
				if (ft_heredoc(p, l) == -1)
					return (-1);
			}
			l = l->next;
		}
		p = p->next;
	}
	return (0);
}
