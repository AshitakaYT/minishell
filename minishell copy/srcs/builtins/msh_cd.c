/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 14:57:43 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/04 18:56:07 by aucousin         ###   ########lyon.fr   */
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

int	msh_cd_noargs(t_process *proc)
{
	char	*tmp;
	char	*tmp2;

	tmp = getcwd(NULL, 0);
	if (!tmp)
		return (-1);
	tmp2 = ft_strjoin(tmp, "/");
	tmp = ft_strjoin(tmp2, proc->cmd[1]);
	printf("tmp = %s\n", tmp);
	if (chdir(tmp))
		ft_putstr_fd("minishell: cd: Not a directory\n", 2);
	free (tmp);
	free(tmp2);
	return (1);
}

int	msh_cd_args(t_minishell *msh)
{
	char	*tmp;
	char	*tmp2;

	tmp = msh_searchenv(msh->envp, "HOME");
	tmp2 = ft_substr(tmp, 5, ft_strlen(tmp) - 5);
	printf("tmp2 = %s\n", tmp2);
	if (!tmp || ft_strlen(tmp2) == 0)
		ft_putstr_fd("cd: HOME not set\n", 2);
	else
		if (chdir(tmp2))
			ft_putstr_fd("minishell: cd: No such file or directory\n", 2);
	free(tmp2);
	return (1);
}

int	msh_cd(t_process *proc, t_minishell *msh)
{
	if (proc->cmd[1])
		return (msh_cd_noargs(proc));
	else
		return (msh_cd_args(msh));
}
