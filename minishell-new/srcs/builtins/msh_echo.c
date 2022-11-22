/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 12:52:35 by aucousin          #+#    #+#             */
/*   Updated: 2022/10/13 14:55:09 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

static int	echo_checkarg(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' && str[i + 1] == 'n')
	{
		i++;
		while (str[i])
		{
			if (str[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	msh_echo(t_process *proc, t_minishell *msh)
{
	int	i;
	int	checkarg;

	(void)msh;
	i = 1;
	checkarg = 0;
	while (proc->cmd[i] && echo_checkarg(proc->cmd[i]))
	{
		i++;
		checkarg++;
	}
	while (proc->cmd[i])
	{
		write(1, proc->cmd[i], ft_strlen(proc->cmd[i]));
		if (proc->cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (!checkarg)
	{
		write(1, "\n", 1);
	}
	return (1);
}
