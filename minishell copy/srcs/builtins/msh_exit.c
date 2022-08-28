/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 23:09:38 by aucousin          #+#    #+#             */
/*   Updated: 2022/07/25 11:06:13 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	msh_exit(t_process *proc, t_minishell *msh)
{
	(void)proc;
	(void)msh;
	write(2, "exit\n", 5);
	exit(1);
}
