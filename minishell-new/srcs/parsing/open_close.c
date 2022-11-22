/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 00:15:11 by aucousin          #+#    #+#             */
/*   Updated: 2022/10/14 18:16:22 by aucousin         ###   ########.fr       */
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

int	ft_rightred(t_process *pipex, t_redir *l)
{
	if (l->type == RRED)
	{
		pipex->file_out = open(l->file,
				O_CREAT | O_WRONLY | O_TRUNC, 0644);
		pipex->append = 0;
	}
	else
	{
		pipex->file_out = open(l->file,
				O_CREAT | O_WRONLY | O_APPEND, 0644);
		pipex->append = 1;
	}
	if (pipex->file_out < 0)
	{
		perror(l->file);
		g_exit = 1;
		return (-1);
	}
	close(pipex->file_out);
	pipex->outfile = ft_strdup(l->file);
	if (!pipex->outfile)
		return (-1);
	return (0);
}

int	ft_leftred(t_process *pipex, t_redir *l)
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
	printf("infile detected : %s\n", pipex->infile);
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
	return (0);
}

int	open_process_files(t_process *pipex)
{
	t_redir	*l;

	l = pipex->redirs;
	while (l)
	{
		if (l->type == RRED || l->type == DRRED)
		{
			if (ft_rightred(pipex, l) == -1)
				return (-1);
		}
		else if (l->type == LRED || l->type == DLRED)
		{
			if (ft_leftred(pipex, l) == -1)
				return (-1);
		}
		l = l->next;
	}
	return (1);
}
