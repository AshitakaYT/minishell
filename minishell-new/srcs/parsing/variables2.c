/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:48:20 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/28 15:47:13 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	ft_handlevar2suite(t_var *var)
{
	ft_freenull(var, TMP);
	var->tmp = ft_strdup(var->cmd);
	if (!var->tmp)
		return (ft_varclear_ret(var));
	free(var->cmd);
	var->cmd = ft_strjoin(var->tmp, var->var);
	if (!var->cmd)
		return (ft_varclear_ret(var));
	ft_freenull(var, TMP);
	return (0);
}

int	ft_handlevar2(t_token *lst, t_minishell *msh, t_var *var)
{
	var->j = ++var->i;
	while (lst->str[var->i] && lst->str[var->i] != ' '
		&& lst->str[var->i] != '$' && lst->str[var->i] != '"'
		&& lst->str[var->i] != 39)
		var->i++;
	ft_freenull(var, TMP);
	var->tmp = ft_substr(lst->str, var->j, var->i - var->j);
	if (!var->tmp)
		return (ft_varclear_ret(var));
	if (ft_strcmp(var->tmp, "?") == 0)
	{
		ft_freenull(var, VAR);
		var->var = ft_itoa(g_exit);
		if (!var->var)
			return (ft_varclear_ret(var));
	}
	else
	{
		ft_freenull(var, VAR);
		var->var = msh_getvar(msh_isintab(msh->envp, var->tmp), msh);
		if (!var->var)
			return (ft_varclear_ret(var));
	}
	return (ft_handlevar2suite(var));
}

int	ft_handledqelse(t_var *var, t_token *lst)
{
	if (var->var)
		free(var->var);
	var->var = ft_substr(lst->str, var->j, var->i - var->j);
	if (!var->var)
	{
		ft_varclear(var);
		return (-1);
	}
	if (var->tmp)
		free(var->tmp);
	var->tmp = ft_strdup(var->cmd);
	if (!var->tmp)
	{
		ft_varclear(var);
		return (-1);
	}
	if (var->cmd)
		free(var->cmd);
	var->cmd = ft_strjoin(var->tmp, var->var);
	if (!var->cmd)
	{
		ft_varclear(var);
		return (-1);
	}
	return (0);
}

char	*ft_handledqfin(t_var *var)
{
	char	*cmd;

	if (!var->cmd)
	{
		var->cmd = ft_strdup("\0");
		if (!var->cmd)
		{
			ft_varclear(var);
			return (NULL);
		}
	}
	if (var->tmp)
	{
		free(var->tmp);
		var->tmp = NULL;
	}
	cmd = ft_strdup(var->cmd);
	if (!cmd)
	{
		ft_varclear(var);
		return (NULL);
	}
	ft_varclear(var);
	return (cmd);
}

char	*ft_handledq(t_token *lst, t_minishell *msh)
{
	t_var	var;

	ft_init_var(&var, 1);
	while (lst->str[var.i] && lst->str[var.i] != '"')
	{
		var.j = var.i;
		while (lst->str[var.i] && lst->str[var.i] != '$'
			&& lst->str[var.i] != '"')
			var.i++;
		if (!var.cmd)
		{
			var.cmd = ft_substr(lst->str, var.j, var.i - var.j);
			if (!var.cmd)
				return (ft_varclear_retnull(&var));
		}
		else
			if (ft_handledqelse(&var, lst) == -1)
				return (ft_varclear_retnull(&var));
		if (lst->str[var.i] == '$')
			if (ft_handlevar2(lst, msh, &var) == -1)
				return (ft_varclear_retnull(&var));
	}
	return (ft_handledqfin(&var));
}
