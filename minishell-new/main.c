/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:51:22 by aucousin          #+#    #+#             */
/*   Updated: 2022/10/15 16:50:15 by aucousin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./hdrs/minishell.h"

int	g_exit;

int	msh_init(t_minishell *msh, char **envp)
{
	msh->status = 1;
	msh->tokens = NULL;
	msh->process = NULL;
	msh->tokenstab = NULL;
	msh->args = NULL;
	msh->line = NULL;
	msh->envp = ft_tabdup(envp);
	if (!msh->envp)
		return (-1);
	if (msh_init_envp(msh) == -1 || msh_init_envp2(msh) == -1)
		return (-1);
	if (ft_add_slash(msh) == -1)
		return (-1);
	g_exit = 0;
	return (0);
}

void	msh_loop2(t_minishell *msh)
{
	if (!ft_checkred(msh->tokens))
	{
		g_exit = 2;
		msh_destroysafe(msh);
	}
	else if (msh_create_process(msh, msh->tokens) == -1)
	{
		write (2, "minishell: msh_loop: msh_create_process failed.\n", 48);
		msh_destroysafe(msh);
	}
	else if (msh->process && msh_parse_redir(msh) == -1)
	{
		write (2, "minishell: msh_loop: msh_parse_redir failed.\n", 45);
		msh_destroysafe(msh);
	}
	else if (ft_heredocs(msh->process) == -1)
	{
		write (2, "minishell: msh_loop: msh_execute failed.\n", 41);
		msh_destroysafe(msh);
	}
	else if (msh_execute(msh) == -1)
	{
		write (2, "minishell: msh_loop: msh_execute failed.\n", 41);
		msh_destroysafe(msh);
	}
}

void	msh_loop(t_minishell *msh)
{
	while (msh->status != FINISHED)
	{
		msh->line = NULL;
		msh->line = readline("minish > ");
		add_history(msh->line);
		if (msh_get_tokens(msh, msh->line) == -1)
		{
			if (!msh->line)
			{
				msh_destroysafe(msh);
				write(2, "exit\n", 5);
				exit(0);
			}
			write (2, "minishell: msh_loop: msh_get_tokens failed.\n", 44);
			msh_destroysafe(msh);
		}
		else
		{
			msh_loop2(msh);
			msh_destroysafe(msh);
		}
	}
	msh_destroy(msh);
}

int	ft_launch_minishell(t_minishell *msh, char *str)
{
	msh->line = ft_strdup(str);
	if (msh_get_tokens(msh, msh->line) == -1)
	{
		if (!msh->line)
		{
			msh_destroysafe(msh);
			write(2, "exit\n", 5);
			exit(0);
		}
		write (2, "minishell: msh_loop: msh_get_tokens failed.\n", 44);
		msh_destroysafe(msh);
	}
	else
	{
		msh_loop2(msh);
		msh_destroysafe(msh);
	}
	return (g_exit);
}

int	main(int argc, char **argv, char **envp)
{
	t_minishell	msh;

	signal(SIGINT, get_signal);
	signal(SIGQUIT, get_signal);
	if (msh_init(&msh, envp) == -1)
	{
		write(2, "malloc failed.\n", 15);
		exit (1);
	}
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		int exit_status = ft_launch_minishell(&msh, argv[2]);
		exit(exit_status);
	}
	else
		msh_loop(&msh);
	return (0);
}
