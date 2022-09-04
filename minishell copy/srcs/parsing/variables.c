/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:35:51 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/04 17:38:09 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

// char	*ft_handlenoq()
// char	*ft_handledq()

char	*msh_getvar(int index, t_minishell *msh)
{
	char	*var;
	int		i;
	int		j;

	i = 0;
	if (index == -1)
	{
		printf("no matches in the environnement.\n");
		return ("\0");
	}
	while (msh->envp[index][i] && msh->envp[index][i] != '=')
		i++;
	if (msh->envp[index][i])
	{
		j = i + 1;
		i++;
		while (msh->envp[index][i])
			i++;
		var = ft_substr(msh->envp[index], j, i - j);
		printf("VAR DANS LE GETVAR = %s\n", var);
	}
	else
		var = NULL;
	return (var);
}

char	*ft_handletxt(t_token *lst, t_minishell *msh)
{
	int		i;
	int		j;
	char	*cmd;
	char	*var;
	char	*tmp;

	i = 0;
	j = 0;
	cmd = NULL;
	while (lst->str[i])
	{
		j = i;
		while (lst->str[i] && lst->str[i] != '$')
			i++;
		if (!cmd)
		{
			cmd = ft_substr(lst->str, j, i - j);
			printf("CREATION DE CMD = %s\n", cmd);
		}
		else
		{
			var = ft_substr(lst->str, j, i - j);
			tmp = ft_strdup(cmd);
			cmd = ft_strjoin(tmp, var);
		}
		if (lst->str[i] == '$')
		{
			j = ++i;
			while (lst->str[i] && lst->str[i] != ' ' && lst->str[i] != '$')
				i++;
			tmp = ft_substr(lst->str, j, i - j);
			if (msh_isintab(msh->envp, tmp))
				var = msh_getvar(msh_isintab(msh->envp, tmp), msh);
			free(tmp);
			tmp = ft_strdup(cmd);
			cmd = ft_strjoin(tmp, var);
			free(tmp);
		}
	}
	return (cmd);
}

char	*ft_handlesq(t_token *lst)
{
	int		i;
	char	*cmd;

	i = 0;
	while (lst->str[i])
		i++;
	cmd = ft_substr(lst->str, 1, i - 2);
	return (cmd);
}


char	*ft_handledq(t_token *lst, t_minishell *msh)
{
	int		i;
	int		j;
	char	*cmd;
	char	*var;
	char	*tmp;

	i = 1;
	j = 1;
	cmd = NULL;
	while (lst->str[i] && lst->str[i] != '"')
	{
		j = i;
		while (lst->str[i] && lst->str[i] != '$' && lst->str[i] != '"')
			i++;
		if (!cmd)
		{
			cmd = ft_substr(lst->str, j, i - j);
		}
		else
		{
			printf("sante bondy on est la\n.");
			var = ft_substr(lst->str, j, i - j);
			tmp = ft_strdup(cmd);
			cmd = ft_strjoin(tmp, var);
		}
		if (lst->str[i] == '$')
		{
			j = ++i;
			while (lst->str[i] && lst->str[i] != ' ' && lst->str[i] != '"' && lst->str[i] != '$')
				i++;
			tmp = ft_substr(lst->str, j, i - j);
			printf("cmd = %s\n", cmd);
			printf("tmp = %s\n", tmp);
			if (msh_isintab(msh->envp, tmp))
			{
				var = msh_getvar(msh_isintab(msh->envp, tmp), msh);
			}
			free(tmp);
			tmp = ft_strdup(cmd);
			printf("tmp2 = %s\n", tmp);
			printf("var = %s\n", var);
			cmd = ft_strjoin(tmp, var);
			printf("cmd = %s\n", cmd);
			free(tmp);
		}
	}
	printf("cmd = %s\n", cmd);
	return (cmd);
}



char	*ft_parsecmd(t_token *lst, t_minishell *msh)
{
	int	i;
	int	j;
	char	*cmd;

	i = 0;
	j = 0;
	cmd = NULL;
	if (lst->type == TEXT)
		cmd = ft_handletxt(lst, msh);
	else if (lst->type == SQTEXT)
		cmd = ft_handlesq(lst);
	else
		cmd = ft_handledq(lst, msh);
	return (cmd);
}

char	**msh_create_cmd(t_token *lst, t_minishell *msh)
{
	char	**cmds;
	int		i;

	i = 0;
	cmds = malloc(sizeof (char *) * (msh_count_cmd(lst) + 1));
	while (lst && lst->type != PIPE)
	{
		if (ft_isred(lst->type))
		{
			lst = lst->next;
		}
		else
		{
			cmds[i] = ft_parsecmd(lst, msh);
			printf("CMD[i] ====== %s\n", cmds[i]);
			i++;
		}
		lst = lst->next;
	}
	cmds[i] = NULL;
	return (cmds);
}
