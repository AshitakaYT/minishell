/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 08:04:34 by aucousin          #+#    #+#             */
/*   Updated: 2022/08/17 15:32:35 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

void	ft_add_slash(t_minishell *pipex)
{
	int		i;
	char	*tmp;

	i = 0;
	while (pipex->paths[i])
	{
		if (pipex->paths[i][ft_strlen(pipex->paths[i]) - 1] != '/')
		{
			tmp = pipex->paths[i];
			pipex->paths[i] = ft_strjoin(tmp, "/");
			free(tmp);
		}
		i++;
	}
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

void	msh_init(t_minishell *msh, char **envp)
{
	char	*path;
	char	*tmp;
	int		i;

	msh->status = 1;
	msh->tokens = NULL;
	msh->process = NULL;
	msh->tokenstab = NULL;
	msh->args = NULL;
	msh->envp = ft_tabdup(envp);
	msh->line = NULL;
	tmp = ft_tabjoin(ft_tablen(envp), envp, "\n");
	if (!tmp)
		return ;
	i = ft_strlen(ft_strstr(tmp, "PATH="));
	path = ft_substr(tmp, ft_strlen(tmp) - i + 5, i - 5);
	free(tmp);
	if (!path)
		return ;
	msh->paths = ft_split(path, ':');
	free(path);
	ft_add_slash(msh);
}
