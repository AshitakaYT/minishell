/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:50:29 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/27 14:06:44 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	msh_pwd(t_process *proc, t_minishell *msh)
{
	char	*str;

	(void)proc;
	(void)msh;
	str = getcwd(NULL, 0);
	if (!str)
	{
		write (2, "minishell: msh_pwd: getcwd failed.\n", 35);
		g_exit = 1;
		return (-1);
	}
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	free(str);
	return (1);
}
