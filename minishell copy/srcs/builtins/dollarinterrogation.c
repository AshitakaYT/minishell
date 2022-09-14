/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarinterrogation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 15:59:54 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/12 16:13:25 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

int	msh_dollarinterrogation(t_minishell *msh)
{
	(void)msh;
	printf("minishell: %d: command not found.\n", g_exit);
	return (0);
}

