/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 23:09:38 by aucousin          #+#    #+#             */
/*   Updated: 2022/10/13 15:16:43 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	ft_freexit(int nb, t_minishell *msh)
{
	msh_destroy(msh);
	ft_putstr_fd("exit\n", 2);
	g_exit = nb;
	exit (nb);
}

int	ft_getsign(char *str, int *i)
{
	int	sign;

	sign = 1;
	while (str[(*i)] == '\f' || str[(*i)] == '\n' || str[(*i)] == '\r'\
			|| str[(*i)] == '\t' || str[(*i)] == '\v' || str[(*i)] == ' ')
		(*i)++;
	if (str[(*i)] == '+' || str[(*i)] == '-')
	{
		if (str[(*i)] == '-')
			sign *= -1;
		(*i)++;
	}
	if (!ft_isdigit(str[(*i)]))
	{
		return (-2);
	}
	return (sign);
}

int	ft_atol_exit(t_minishell *msh, t_process *proc)
{
	unsigned long long	nb;
	unsigned long long	max;
	int					i;
	int					sign;

	i = 0;
	nb = 0;
	max = 9223372036854775807;
	sign = ft_getsign(proc->cmd[1], &i);
	while (proc->cmd[1][i] >= '0' && proc->cmd[1][i] <= '9')
	{
		nb = nb * 10 + proc->cmd[1][i] - '0';
		i++;
	}
	if ((nb > max && sign == 1) || sign == -2 || \
	(nb > max + 1 && sign == -1) || (proc->cmd[1][i] != '\0'))
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		nb = 255;
		sign = 1;
	}
	ft_freexit(nb * sign, msh);
	return (-1);
}

void	msh_exit(t_process *proc, t_minishell *msh)
{
	int	i;

	i = 0;
	while (proc->cmd[i])
		i++;
	if (i > 2)
	{
		g_exit = 1;
		ft_putstr_fd("minishell: exit: too many arguments.\n", 2);
	}
	else if (i == 1)
		ft_freexit(0, msh);
	else
		ft_atol_exit(msh, proc);
}
