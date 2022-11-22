/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:35:51 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/26 19:11:51 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

char	*msh_novar(void)
{
	char	*var;

	write(2, "no matches in the environnement.\n", 33);
	var = malloc(sizeof(char));
	if (!var)
		return (NULL);
	var[0] = '\0';
	return (var);
}

char	*msh_getvar(int index, t_minishell *msh)
{
	char	*var;
	int		i;
	int		j;

	i = 0;
	if (index == -1)
		return (msh_novar());
	while (msh->envp[index][i] && msh->envp[index][i] != '=')
		i++;
	if (msh->envp[index][i])
	{
		j = i + 1;
		i++;
		while (msh->envp[index][i])
			i++;
		var = ft_substr(msh->envp[index], j, i - j);
		if (!var)
			return (NULL);
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
