/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 21:37:15 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/30 11:30:17 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	ft_printtoken(t_token *list)
{
	int	i;

	i = 0;
	while (list)
	{
		ft_printf("-----------------------------------\n");
		ft_printf("| i = %d                            \n", i);
		ft_printf("| list->str : %s            \n", list->str);
		ft_printf("| list->type : %d            \n", list->type);
		ft_printf("| list->islinked : %d            \n", list->islinked);
		ft_printf("-----------------------------------\n");
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
		ft_printf("-----------------------------------\n");
		ft_printf("| i = %d                            \n", i);
		ft_printf("| list->file : %s            \n", list->file);
		ft_printf("| list->type : %d            \n", list->type);
		ft_printf("| list->heredoc : %s            \n", list->heredoc);
		ft_printf("-----------------------------------\n");
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
		ft_printf("%s\n", tab[i]);
		i++;
	}
}

void	ft_printprocess(t_process *list)
{
	int	i;

	i = 0;
	while (list)
	{
		ft_printf("-----------------------------------\n");
		ft_printf("| i = %d                            \n", i);
		ft_printf("| infile = %s                            \n", list->infile);
		ft_printf("| outfile = %s                            \n", list->outfile);
		ft_printf("| heredoc = %d                      \n", list->heredoc);
		ft_printf("| heredocs = %d                      \n", list->heredocs);
		ft_printf("| piped = %d                      \n", list->piped);
		ft_printf("| process->cmd :            \n");
		ft_print_tab(list->cmd);
		ft_printf("| process->redirs :           \n");
		ft_printredirs(list->redirs);
		ft_printf("-----------------------------------\n");
		list = list->next;
		i++;
	}
}
