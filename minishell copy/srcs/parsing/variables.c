/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:35:51 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/12 19:00:09 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

char	*msh_getvar(int index, t_minishell *msh)
{
	char	*var;
	int		i;
	int		j;

	i = 0;
	if (index == -1)
	{
		printf("no matches in the environnement.\n");
		return ("\0");
	}
	while (msh->envp[index][i] && msh->envp[index][i] != '=')
		i++;
	if (msh->envp[index][i])
	{
		j = i + 1;
		i++;
		while (msh->envp[index][i])
			i++;
		var = ft_substr(msh->envp[index], j, i - j);
		printf("VAR DANS LE GETVAR = %s\n", var);
	}
	else
		var = NULL;
	return (var);
}

void	ft_init_var(t_var *var, int x)
{
	var->cmd = NULL;
	var->i = x;
	var->j = x;
	var->tmp = NULL;
	var->var = NULL;
}

void	ft_handlevar(t_token *lst, t_minishell *msh, t_var *var)
{
	var->j = ++var->i;
	while (lst->str[var->i] && lst->str[var->i] != ' '
		&& lst->str[var->i] != '$')
		var->i++;
	var->tmp = ft_substr(lst->str, var->j, var->i - var->j);
	if (msh_isintab(msh->envp, var->tmp))
		var->var = msh_getvar(msh_isintab(msh->envp, var->tmp), msh);
	if (ft_strcmp(var->tmp, "?") == 0)
		var->var = ft_itoa(g_exit);
	free(var->tmp);
	var->tmp = ft_strdup(var->cmd);
	var->cmd = ft_strjoin(var->tmp, var->var);
	free(var->tmp);
}

char	*ft_handletxt(t_token *lst, t_minishell *msh)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	ft_init_var(var, 0);
	while (lst->str[var->i])
	{
		var->j = var->i;
		while (lst->str[var->i] && lst->str[var->i] != '$')
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
			ft_handlevar(lst, msh, var);
	}
	return (var->cmd);
}

char	*ft_handlesq(t_token *lst)
{
	int		i;
	char	*cmd;

	i = 0;
	while (lst->str[i])
		i++;
	cmd = ft_substr(lst->str, 1, i - 2);
	return (cmd);
}
