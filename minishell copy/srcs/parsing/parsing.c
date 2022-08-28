/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 09:20:25 by aucousin          #+#    #+#             */
/*   Updated: 2022/08/25 17:10:43 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	ft_checkred(t_token *list)
{
	if (!list)
		return (0);
	while (list)
	{
		if ((ft_isred(list->type) && !list->next)
			|| (list->type == PIPE && !list->next))
		{
			printf("bash: syntax error near unexpected token `newline'\n");
			return (0);
		}
		else if ((ft_isred(list->type) && !ft_istxt(list->next->type))
			|| (list->type == PIPE && list->next->type == PIPE))
		{
			printf("bash: syntax error near unexpected token `%s'\n", list->str);
			return (0);
		}
		list = list->next;
	}
	return (1);
}

void	msh_get_tokens(t_minishell *msh, char *line)
{
	int		i;
	int		index;
	t_token	*token;

	i = 0;
	index = 0;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] && ft_isprintsh(line[i]))
		{
			token = ft_tokennew(ft_strndup(&line[i], ft_len_alnum(&line[i])), TEXT, index);
			i += ft_len_alnum(&line[i]);
		}
		else if (line[i] && (line[i]) == 39)
		{
			if (ft_lenquote(&line[i]) == -1)
				ft_exit_fd(1, "unvalid single quote.");
			token = ft_tokennew(ft_strndup(&line[i], ft_lenquote(&line[i])), SQTEXT, index);
			i += ft_lenquote(&line[i]);
		}
		else if (line[i] && (line[i]) == '"')
		{
			token = ft_tokennew(ft_strndup(&line[i], ft_lendbquote(&line[i])), DQTEXT, index);
			i += ft_lendbquote(&line[i]);
		}
		else if (line[i] && (line[i]) == '>' && ((line[i + 1] && line[i + 1] != '>') || !line[i + 1]))
		{
			token = ft_tokennew(ft_strndup(&line[i], 1), RRED, index);
			i += 1;
		}
		else if (line[i] && (line[i]) == '>' && line[i + 1] && line[i + 1] == '>')
		{
			token = ft_tokennew(ft_strndup(&line[i], 2), DRRED, index);
			i += 2;
		}
		else if (line[i] && (line[i]) == '<' && ((line[i + 1] && line[i + 1] != '<') || !line[i + 1]))
		{
			token = ft_tokennew(ft_strndup(&line[i], 1), LRED, index);
			i += 1;
		}
		else if (line[i] && (line[i]) == '<' && line[i + 1] && line[i + 1] == '<')
		{
			token = ft_tokennew(ft_strndup(&line[i], 2), DLRED, index);
			i += 2;
		}
		else if (line[i] && (line[i]) == '|')
		{
			token = ft_tokennew(ft_strndup(&line[i], 1), PIPE, index);
			i += 1;
		}
		ft_tokenadd_back(&msh->tokens, token);
		token = NULL;
	}
}

int		msh_count_cmd(t_token *lst)
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
				ft_rediradd_back(&process->redirs ,redir);
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

/*void	msh_get_redirs(t_minishell *msh, t_token *lst, t_process *process)
{
	t_redir	*redir;

	while (lst)
	{
		if (ft_isred(lst->type))
		{
			redir = ft_redirnew(NULL, lst->type, lst->next->str);
			ft_rediradd_back(&process->redirs ,redir);
			lst = lst->next;
		}
		lst = lst->next;
	}

}*/

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
