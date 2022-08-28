/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:51:22 by aucousin          #+#    #+#             */
/*   Updated: 2022/08/17 15:52:13 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "./hdrs/minishell.h"

void	msh_loop(char **envp)
{
	t_minishell	msh;
	char		*tmp;

	msh_init(&msh, envp);
//	signal(SIGINT, sig_quit);
//	signal(SIGQUIT, action);
	while (msh.status != FINISHED)
	{
		write(1, "minish >  ", 9);
		tmp = NULL;
		msh.line = readline(tmp);
		free(tmp);
		add_history(msh.line);
		msh_get_tokens(&msh, msh.line);
		ft_printtoken(msh.tokens);
		if (!ft_checkred(msh.tokens))
		{
			printf("INVALID LINE !!!!!\n");
			ft_tokensclear(&msh.tokens);
			return ;
		}
		// printf("line = %s\n", msh.line);
		msh_create_process(&msh, msh.tokens);
		ft_tokensclear(&msh.tokens);
		ft_heredocs(msh.process);
		msh_parse_redir(&msh);
		// printf("on va la ? \n");
		// ft_printprocess(msh.process);
		msh_execute(&msh);
		ft_processclear(&msh.process);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	if (!envp[0])
	{
		printf("please don't destry your environnement, it's not eco-friendly :@\n");
		return (0);
	}
	//msh_env(envp);
	msh_loop(envp);
//	rl_clear_history();
}