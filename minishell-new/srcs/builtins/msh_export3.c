/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_export3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 18:30:36 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/30 11:26:51 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

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
	ft_printf("\n");
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

int	verif_args_env(char *str)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[0]) == 1 || str[0] == '=')
		return (-1);
	while (str[i])
	{
		if (str[i] == '=')
			break ;
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
			return (-1);
		i++;
	}
	return (0);
}
