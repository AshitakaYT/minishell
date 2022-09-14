/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 00:15:11 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/14 16:20:15 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	exit_perror(char *error, int code)
{
	perror(error);
	exit(code);
}

int	close_files(t_process *pipex)
{
	close(pipex->file_in);
	close(pipex->file_out);
	return (0);
}

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
			pipex->outfile = l->file;
		}
		else if (l->type == LRED || l->type == DLRED)
		{
			pipex->file_in = open(l->file, O_RDONLY);
			pipex->infile = l->file;
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
			printf("type = %d\n", l->type);
			if (l->type == DLRED)
				ft_heredoc(l);
			l = l->next;
		}
		p = p->next;
	}
}
