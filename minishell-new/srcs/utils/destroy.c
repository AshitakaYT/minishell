/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 11:02:25 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/27 13:02:08 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	msh_destroy(t_minishell *msh)
{
	if (msh->tokens)
		ft_tokensclear(&msh->tokens);
	if (msh->process)
		ft_processclear(&msh->process);
	if (msh->args)
	{
		ft_free_tab(msh->args);
		msh->args = NULL;
	}
	if (msh->envp)
	{
		ft_free_tab(msh->envp);
		msh->envp = NULL;
	}
	if (msh->paths)
	{
		ft_free_tab(msh->paths);
		msh->paths = NULL;
	}
	if (msh->line)
	{
		free(msh->line);
		msh->line = NULL;
	}
	rl_clear_history();
}

void	msh_destroysafe(t_minishell *msh)
{
	if (msh->tokens)
	{
		ft_tokensclear(&msh->tokens);
		msh->tokens = NULL;
	}
	if (msh->process)
	{
		ft_processclear(&msh->process);
		msh->process = NULL;
	}
	if (msh->args)
	{
		ft_free_tab(msh->args);
		msh->args = NULL;
	}
	if (msh->line)
	{
		free(msh->line);
		msh->line = NULL;
	}
}

void	ft_exit_fd(int fd, char *str)
{
	int	i;

	i = ft_strlen(str);
	write(fd, str, i);
	exit(EXIT_FAILURE);
}

char	**ft_tabdup(char **tab)
{
	int		i;
	char	**new;

	new = malloc(sizeof(char *) * (ft_tablen(tab) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < ft_tablen(tab))
	{
		new[i] = ft_strdup(tab[i]);
		if (!new[i])
			return (NULL);
		i++;
	}
	new[i] = 0;
	return (new);
}
