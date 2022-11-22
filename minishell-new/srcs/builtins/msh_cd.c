/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:57:43 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/28 15:27:28 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

char	*msh_searchenv(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, ft_strlen(str)))
			return (env[i]);
		i++;
	}
	return (NULL);
}

int	msh_cd_args(t_process *proc)
{
	char	*tmp;
	char	*tmp2;

	if (chdir(proc->cmd[1]))
	{	
		tmp = getcwd(NULL, 0);
		if (!tmp)
			return (-1);
		tmp2 = ft_strjoin(tmp, "/");
		if (!tmp2)
			return (-1);
		free(tmp);
		tmp = ft_strjoin(tmp2, proc->cmd[1]);
		if (!tmp)
			return (-1);
		if (chdir(tmp))
		{
			ft_putstr_fd("minishell: cd: Not a directory\n", 2);
			g_exit = 1;
		}
		free (tmp);
		free(tmp2);
	}
	return (1);
}

int	msh_cd_noargs(t_minishell *msh)
{
	char	*tmp;
	char	*tmp2;

	tmp = msh_searchenv(msh->envp, "HOME=");
	if (!tmp)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		g_exit = 1;
		return (1);
	}
	tmp2 = ft_substr(tmp, 5, ft_strlen(tmp) - 5);
	if (!tmp2)
		return (-1);
	if (ft_strlen(tmp2) == 0)
	{
		ft_putstr_fd("cd: HOME not set.\n", 2);
		g_exit = 1;
	}
	else if (chdir(tmp2))
	{
		ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
		g_exit = 1;
	}
	free(tmp2);
	return (0);
}

int	msh_cd(t_process *proc, t_minishell *msh)
{
	if (proc->cmd[1])
		return (msh_cd_args(proc));
	else
		return (msh_cd_noargs(msh));
}
