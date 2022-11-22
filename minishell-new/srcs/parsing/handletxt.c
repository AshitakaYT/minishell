/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handletxt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:09:59 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/27 11:43:00 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	ft_handlevarsuite(t_var *var)
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

int	ft_handlevar(t_token *lst, t_minishell *msh, t_var *var)
{
	var->j = ++var->i;
	while (lst->str[var->i] && lst->str[var->i] != ' '
		&& lst->str[var->i] != '$')
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
	return (ft_handlevarsuite(var));
}

int	ft_handletxtelse(t_var *var, t_token *lst)
{
	ft_freenull(var, VAR);
	var->var = ft_substr(lst->str, var->j, var->i - var->j);
	if (!var->var)
		return (ft_varclear_ret(var));
	ft_freenull(var, TMP);
	var->tmp = ft_strdup(var->cmd);
	if (!var->tmp)
		return (ft_varclear_ret(var));
	ft_freenull(var, CMD);
	var->cmd = ft_strjoin(var->tmp, var->var);
	if (!var->cmd)
		return (ft_varclear_ret(var));
	return (0);
}

char	*ft_handletxtfin(t_var *var)
{
	char	*cmd;

	cmd = ft_strdup(var->cmd);
	if (!cmd)
		return (ft_varclear_retnull(var));
	ft_varclear(var);
	return (cmd);
}

char	*ft_handletxt(t_token *lst, t_minishell *msh)
{
	t_var	var;

	ft_init_var(&var, 0);
	while (lst->str[var.i])
	{
		var.j = var.i;
		while (lst->str[var.i] && lst->str[var.i] != '$')
			var.i++;
		if (!var.cmd)
		{
			var.cmd = ft_substr(lst->str, var.j, var.i - var.j);
			if (!var.cmd)
				return (ft_varclear_retnull(&var));
		}
		else
			if (ft_handletxtelse(&var, lst) == -1)
				return (ft_varclear_retnull(&var));
		if (lst->str[var.i] == '$')
		{
			if (ft_handlevar(lst, msh, &var) == -1)
				return (ft_varclear_retnull(&var));
		}
	}
	return (ft_handletxtfin(&var));
}
