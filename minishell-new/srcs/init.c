/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 08:04:34 by aucousin          #+#    #+#             */
/*   Updated: 2022/10/13 14:56:45 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdrs/minishell.h"

int	ft_add_slash(t_minishell *pipex)
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
			if (!pipex->paths[i])
			{
				free(tmp);
				return (-1);
			}
			free(tmp);
		}
		i++;
	}
	return (0);
}

int	msh_update_shlvl(t_minishell *msh, int i, int j)
{
	int		nb;
	char	*tmp;
	char	*tmp2;

	while (msh->envp[i][j] && msh->envp[i][j] != '=')
		j++;
	if (msh->envp[i][++j])
	{
		nb = ft_atoi(&msh->envp[i][j]);
		tmp = ft_itoa(nb + 1);
		if (!tmp)
			return (-1);
		tmp2 = ft_substr(msh->envp[i], 0, j);
		if (!tmp2)
			return (ft_freeret(tmp));
		free(msh->envp[i]);
		msh->envp[i] = ft_strjoin(tmp2, tmp);
		free(tmp2);
		free(tmp);
		if (!msh->envp[i])
			return (-1);
	}
	return (0);
}

int	msh_init_pwd(t_minishell *msh)
{
	char	*pwd;
	char	*tmp;

	pwd = getcwd(NULL, 10);
	if (!pwd)
		return (-1);
	if (msh_isintab(msh->envp, "PWD") == -1)
	{
		tmp = ft_strjoin("PWD=", pwd);
		if (!tmp)
		{
			free(pwd);
			return (-1);
		}
		msh->envp = msh_realloc_env(msh, tmp);
		free(tmp);
		if (!msh->envp)
		{
			free(pwd);
			return (-1);
		}
	}
	free(pwd);
	return (0);
}

int	msh_init_envp(t_minishell *msh)
{
	if (msh_isintab(msh->envp, "SHLVL") == -1)
	{
		msh->envp = msh_realloc_env(msh, "SHLVL=1");
		if (!msh->envp)
			return (-1);
	}
	else
	{
		if (msh_update_shlvl(msh,
				msh_isintab(msh->envp, "SHLVL"), 0) == -1)
			return (-1);
	}
	if (msh_init_pwd(msh) == -1)
		return (-1);
	if (msh_isintab(msh->envp, "OLDPWD") == -1)
	{
		msh->envp = msh_realloc_env(msh, "OLDPWD");
		if (!msh->envp)
			return (-1);
	}
	return (0);
}

int	msh_init_envp2(t_minishell *msh)
{
	char	*path;
	int		i;

	if (msh_isintab(msh->envp, "PATH") != -1)
	{
		i = ft_strlen(msh->envp[msh_isintab(msh->envp, "PATH")]);
		path = ft_substr(msh->envp[msh_isintab(msh->envp, "PATH")], 5, i - 5);
		if (!path)
			return (-1);
		msh->paths = ft_split(path, ':');
		free(path);
		if (!msh->paths)
			return (-1);
	}
	else
	{
		msh->paths = malloc(sizeof(char *) * 2);
		if (!msh->paths)
			return (-1);
		msh->paths[0] = ft_strdup(".");
		if (!msh->paths[0])
			return (-1);
		msh->paths[1] = 0;
	}
	return (0);
}
