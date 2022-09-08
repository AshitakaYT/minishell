/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:48:20 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/04 19:16:49 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	ft_handlevar2(t_token *lst, t_minishell *msh, t_var *var)
{
	var->j = ++var->i;
	while (lst->str[var->i] && lst->str[var->i] != ' '
		&& lst->str[var->i] != '$' && lst->str[var->i] != '"')
		var->i++;
	var->tmp = ft_substr(lst->str, var->j, var->i - var->j);
	if (msh_isintab(msh->envp, var->tmp))
		var->var = msh_getvar(msh_isintab(msh->envp, var->tmp), msh);
	free(var->tmp);
	var->tmp = ft_strdup(var->cmd);
	var->cmd = ft_strjoin(var->tmp, var->var);
	free(var->tmp);
}

char	*ft_handledq(t_token *lst, t_minishell *msh)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	ft_init_var(var, 1);
	while (lst->str[var->i] && lst->str[var->i] != '"')
	{
		var->j = var->i;
		while (lst->str[var->i] && lst->str[var->i] != '$'
			&& lst->str[var->i] != '"')
			var->i++;
		if (!var->cmd)
			var->cmd = ft_substr(lst->str, var->j, var->i - var->j);
		else
		{
			var->var = ft_substr(lst->str, var->j, var->i - var->j);
			var->tmp = ft_strdup(var->cmd);
			var->cmd = ft_strjoin(var->tmp, var->var);
		}
		if (lst->str[var->i] == '$')
			ft_handlevar2(lst, msh, var);
	}
	return (var->cmd);
}

char	*ft_parsecmd(t_token *lst, t_minishell *msh)
{
	int		i;
	int		j;
	char	*cmd;

	i = 0;
	j = 0;
	cmd = NULL;
	if (lst->type == TEXT)
		cmd = ft_handletxt(lst, msh);
	else if (lst->type == SQTEXT)
		cmd = ft_handlesq(lst);
	else
		cmd = ft_handledq(lst, msh);
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
			cmds[i] = ft_parsecmd(lst, msh);
			printf("CMD[i] ====== %s\n", cmds[i]);
			i++;
		}
		lst = lst->next;
	}
	cmds[i] = NULL;
	return (cmds);
}
