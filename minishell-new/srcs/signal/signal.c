/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:12:29 by aucousin          #+#    #+#             */
/*   Updated: 2022/09/27 14:23:34 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../hdrs/minishell.h"

void	delsig(void)
{
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("  \b\b", 2);
}

void	get_signal(int sig)
{
	if (sig == SIGINT)
	{
		if (g_exit == INHEREDOC_FORK)
			exit(1);
		else if (g_exit != INEXECVE && g_exit != INHEREDOC)
		{
			ft_putchar_fd('\n', 2);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		g_exit = SIGC;
	}
	else if (sig == SIGQUIT)
	{
		if (g_exit == INHEREDOC)
			return ;
		else if (g_exit == INEXECVE)
			g_exit = 131;
		else
			delsig();
	}
}

void	sigfork(int sig)
{
	if (SIGINT == sig)
		g_exit = SIGC;
}
