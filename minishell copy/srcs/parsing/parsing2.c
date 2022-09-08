/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 17:04:59 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/07 17:07:34 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	msh_get_tokens(t_minishell *msh, char *line)
{
	int		i;
	int		linked;
	t_token	*token;

	i = 0;
	linked = 0;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] && ft_isprintsh(line[i]))
			token = msh_parse_txt(line, &linked, &i);
		else if (line[i] && (line[i]) == 39)
			token = msh_parse_sq(line, &linked, &i);
		else if (line[i] && (line[i]) == '"')
			token = msh_parse_dbq(line, &linked, &i);
		else if (ft_isred(line[i]))
			token = msh_parse_red(line, &linked, &i);
		else if (line[i] && (line[i]) == '|')
			token = ft_tokennew(ft_strndup(&line[i++], 1), PIPE, linked);
		ft_tokenadd_back(&msh->tokens, token);
		token = NULL;
	}
}

int	msh_count_cmd(t_token *lst)
{
	int	i;

	i = 0;
	while (lst && lst->type != PIPE)
	{
		if (ft_isred(lst->type))
		{
			lst = lst->next;
		}
		else
			i++;
		lst = lst->next;
	}
	printf("I COUNT CMD = %d\n", i);
	return (i);
}

void	msh_create_process(t_minishell *msh, t_token *lst)
{
	t_process	*process;
	t_process	*tmp;
	t_redir		*redir;

	if (!lst)
		return ;
	process = ft_processnew(msh_create_cmd(lst, msh), 0, NULL);
	ft_processadd_back(&msh->process, process);
	while (lst)
	{
		while (lst && lst->type != PIPE)
		{
			if (ft_isred(lst->type))
			{
				redir = ft_redirnew(NULL, lst->type, lst->next->str);
				ft_rediradd_back(&process->redirs, redir);
				lst = lst->next;
			}
			lst = lst->next;
		}
		if (lst)
		{
			tmp = process;
			process = ft_processnew(msh_create_cmd(lst->next, msh), 1, tmp);
			lst = lst->next;
			ft_processadd_back(&msh->process, process);
		}
	}
}

int	msh_parse_redir(t_minishell *msh)
{
	t_process *l;

	l = msh->process;
	while (l)
	{
		open_process_files(l);
		l = l->next;
	}
	return (1);
}
