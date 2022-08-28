/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 10:11:10 by aucousin          #+#    #+#             */
/*   Updated: 2022/08/17 15:52:13 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

static int	ft_strscmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

void	ft_sort_string_tab(char **tab)
{
	int		i;
	int		j;
	int		size;
	char	*swap;

	size = 0;
	while (tab[size])
		size++;
	i = 0;
	while (i < size)
	{
		j = i;
		while (j < size)
		{
			if (ft_strscmp(tab[j], tab[i]) < 0)
			{
				swap = tab[j];
				tab[j] = tab[i];
				tab[i] = swap;
				j = i;
			}
			j++;
		}
		i++;
	}
}

char	*ft_strdupexport(char *src)
{
	char	*dest;
	int		i;
	int		y;

	dest = malloc((ft_strlen((const char *)src) + 1 + 2) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	y = 0;
	while (i < ft_strlen((const char *)src))
	{
		dest[y] = src[i];
		if (src[i] == '=' && src[i + 1] && i == y)
			dest[++y] = '"';
		i++;
		y++;
	}
	dest[y] = '"';
	dest[++y] = '\0';
	return (dest);
}

void	msh_printfexport(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("declare -x %s\n", tab[i]);
		i++;
	}
}

int	msh_exportcount(char **env)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (env[i])
	{
		if (ft_strchr(env[i], '='))
			count++;
		i++;
	}
	return (count);
}

/*
void	msh_export_noargs(t_minishell *msh)
{
	int		i;
	int		y;
	char	**res;

	i = 0;
	y = 0;
	res = malloc(sizeof(char *) * msh_exportcount(msh->envp) + 1);
	while (msh->envp[i])
	{
		if (ft_strchr(msh->envp[i], '='))
			res[y++] = ft_strdupexport(msh->envp[i]);
		i++;
	}
	res[y] = 0;
	ft_sort_string_tab(res);
	ft_free_tab(res);
}
*/

void	ft_printexportline(char *str)
{
	int	i;
	int	mybool;

	i = 0;
	mybool = 0;
	ft_putstr_fd("declare -x ", 1);
	while (str[i])
	{
		ft_putchar_fd(str[i], 1);
		if (str[i] == '=' && mybool == 0)
		{
			ft_putchar_fd('"', 1);
			mybool = 1;
		}
		i++;
	}
	if (mybool == 1)
		ft_putchar_fd('"', 1);
	printf("\n");
}

void	msh_export_noargs(t_minishell *msh)
{
	int	i;

	i = 0;
	ft_sort_string_tab(msh->envp);
	while (msh->envp[i])
	{
		ft_printexportline(msh->envp[i]);
		i++;
	}
}

char	**msh_realloc_env(t_minishell *msh, char *str)
{
	char	**new;
	int		i;

	i = 0;
	new = malloc(sizeof(char *) * (ft_tablen(msh->envp) + 2));
	while (i < ft_tablen(msh->envp))
	{
		new[i] = ft_strdup(msh->envp[i]);
		i++;
	}
	new[i] = ft_strdup(str);
	i++;
	new[i] = 0;
	ft_free_tab(msh->envp);
	msh->envp = new;
	return (new);
}

int	msh_isintab(char **tab, char *str)
{
	int	i;
	int	j;
	
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j] && str[j] && tab[i][j] == str[j] && tab[i][j] != '=')
		{
			j++;
			if ((!tab[i][j] && !str[j]) || (tab[i][j] == '=' && (str[j] == '=' || !str[j])))
				return (i);
		}
		i++;
	}
	return (-1);
}

void	msh_update_env(t_minishell *msh, char *cmd, int i)
{
	free(msh->envp[i]);
	msh->envp[i] = ft_strdup(cmd);
}

void	msh_export_args(t_process *proc, t_minishell *msh)
{
	int	i;

	i = 0;
	while (proc->cmd[i])
	{
		if (msh_isintab(msh->envp, proc->cmd[i]) == -1)
		{
			msh_realloc_env(msh, proc->cmd[i]);
		}
		else if (msh_isintab(msh->envp, proc->cmd[i]))
		{
			msh_update_env(msh, proc->cmd[i], msh_isintab(msh->envp, proc->cmd[i]));
		}
		i++;
	}
}

void	msh_export(t_process *proc, t_minishell *msh)
{
	if (!proc->cmd[1])
	{
		msh_export_noargs(msh);
	}
	else
	{
		msh_export_args(proc, msh);
	}
}
