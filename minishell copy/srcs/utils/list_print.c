/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:37:15 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/07 16:16:39 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	ft_printtoken(t_token *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("-----------------------------------\n");
		printf("| i = %d                            \n", i);
		printf("| list->str : %s            \n", list->str);
		printf("| list->type : %d            \n", list->type);
		printf("| list->islinked : %d            \n", list->islinked);
		printf("-----------------------------------\n");
		list = list->next;
		i++;
	}
}

void	ft_printredirs(t_redir *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("-----------------------------------\n");
		printf("| i = %d                            \n", i);
		printf("| list->file : %s            \n", list->file);
		printf("| list->type : %d            \n", list->type);
		printf("| list->heredoc : %s            \n", list->heredoc);
		printf("-----------------------------------\n");
		list = list->next;
		i++;
	}
}

void	ft_print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}

void	ft_printprocess(t_process *list)
{
	int	i;

	i = 0;
	while (list)
	{
		printf("-----------------------------------\n");
		printf("| i = %d                            \n", i);
		printf("| infile = %s                            \n", list->infile);
		printf("| outfile = %s                            \n", list->outfile);
		printf("| heredoc = %d                      \n", list->heredoc);
		printf("| heredocs = %d                      \n", list->heredocs);
		printf("| piped = %d                      \n", list->piped);
		printf("| process->cmd :            \n");
		ft_print_tab(list->cmd);
		printf("| process->redirs :           \n");
		ft_printredirs(list->redirs);
		printf("-----------------------------------\n");
		list = list->next;
		i++;
	}
}
