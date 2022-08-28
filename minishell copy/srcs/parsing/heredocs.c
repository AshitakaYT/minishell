/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 16:13:38 by aucousin          #+#    #+#             */
/*   Updated: 2022/08/17 15:52:13 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	ft_heredoc(t_redir *heredoc)
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
		heredoc->heredoc = ft_strjoin(heredoc->tmp, heredoc->line);
		if (ft_strcmp(heredoc->file, heredoc->line) == 0)
		{
			printf("heredoc = %s\n", heredoc->heredoc);
			break ;
		}
		heredoc->tmp = heredoc->heredoc;
		heredoc->heredoc = ft_strjoin(heredoc->tmp, "\n");
		free(tmp);
	}
}
