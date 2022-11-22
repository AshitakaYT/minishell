/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variableutils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 18:11:57 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/27 11:00:35 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	ft_varclear_ret(t_var *var)
{
	ft_varclear(var);
	return (-1);
}

char	*ft_varclear_retnull(t_var *var)
{
	ft_varclear(var);
	return (NULL);
}

int	ft_freeret(char *str)
{
	free(str);
	return (-1);
}

void	ft_freenull(t_var *var, int nb)
{
	if (nb == TMP)
	{
		if (var->tmp)
		{
			free(var->tmp);
			var->tmp = NULL;
		}
	}
	else if (nb == VAR)
	{
		if (var->var)
		{
			free(var->var);
			var->var = NULL;
		}
	}
	else
	{
		if (var->cmd)
		{
			free(var->cmd);
			var->cmd = NULL;
		}
	}
}

char	**ft_freetab_retnull(char **tab)
{
	ft_free_tab(tab);
	return (NULL);
}
