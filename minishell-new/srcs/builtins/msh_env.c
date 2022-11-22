/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 22:55:39 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/30 11:25:58 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	msh_env(t_process *proc, t_minishell *msh)
{
	int	i;

	i = 0;
	(void)proc;
	while (msh->envp[i])
	{
		if (strchr(msh->envp[i], '='))
			ft_printf("%s\n", msh->envp[i]);
		i++;
	}
}
