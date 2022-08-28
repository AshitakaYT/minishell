/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:35:51 by aucousin          #+#    #+#             */
/*   Updated: 2022/08/25 17:24:48 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

// char	*ft_handlenoq()
// char	*ft_handledq()

char	*msh_getvar(int index, t_minishell *msh)
{
	char	*var;
	int		i;
	int		j;

	i = 0;
	while (msh->envp[index][i] && msh->envp[index][i] != '=')
		i++;
	if (msh->envp[index][i])
	{
		i++;
		j = i;
		while (msh->envp[index][i])
		{
			
		}
	}
}

char	*ft_parsecmd(t_token *lst, t_minishell *msh)
{
	int	i;
	int	j;
	char	*cmd;
	char	*var;
	char	*truevar;
	char	*tmp;

	i = 0;
	j = 1;
	cmd = NULL;
	if (lst->type == SQTEXT)
		return (lst->str);
	else if (lst->type == DQTEXT)
	{
		while (lst->str[i])
		{
			while (lst->str[i] && lst->str[i] != '$')
				i++;
			cmd = ft_substr(lst->str, j, i - j);
			if (lst->str[i] == '$')
			{
				j = i;
				while (lst->str[i] && lst->str[i] != ' ' && lst->str[i] != '"')
					i++;
				var = ft_substr(lst->str, j, i - j);
				if (msh_isintab(msh->envp, var))
				{
					truevar = msh_getvar(msh_isintab(msh->envp, var), msh);
				}
				tmp = ft_strdup(cmd);
				cmd = ft_strjoin(tmp, var);
			}
		}
	}
	else
	{
		while (lst->str[i])
		{
			while (lst->str[i] && lst->str[i] != '$')
				i++;
			cmd = ft_substr(lst->str, j, i - j);
		}
	}
	return (cmd);
}

char	**msh_create_cmd(t_token *lst, t_minishell *msh)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = malloc(sizeof (char *) * (msh_count_cmd(lst) + 1));
	while (lst && lst->type != PIPE)
	{
		if (ft_isred(lst->type))
		{
			lst = lst->next;
		}
		else
		{
			cmds[i] = ft_parsecmd(lst);
			printf("CMD[i] ====== %s\n", cmds[i]);
			i++;
		}
		lst = lst->next;
	}
	cmds[i] = NULL;
	return (cmds);
}
