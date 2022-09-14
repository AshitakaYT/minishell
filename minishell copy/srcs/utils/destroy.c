/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:02:25 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/12 15:36:39 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	msh_destroy(t_minishell *msh)
{
	if (msh->tokens)
		ft_tokensclear(&msh->tokens);
	if (msh->process)
		ft_processclear(&msh->process);
	if (msh->tokenstab)
		ft_free_tab(msh->tokenstab);
	if (msh->args)
		ft_free_tab(msh->args);
	if (msh->envp)
		ft_free_tab(msh->envp);
	if (msh->paths)
		ft_free_tab(msh->paths);
	if (msh->line)
		free(msh->line);
}