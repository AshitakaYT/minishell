/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aucousin <aucousin@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 10:37:47 by aucousin          #+#    #+#             */
/*   Updated: 2022/08/25 16:53:07 by aucousin         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 2048
# define TOKEN_BUFFSIZE 64
# define TOKEN_DELIMITERS "\t\r\n\a"
# define TEXT 1
# define SQTEXT 8
# define DQTEXT 9
# define PIPE 2
# define DPIPE 3
# define RRED 4
# define DRRED 5
# define LRED 6
# define DLRED 7

# define READING 1
# define FINISHED 0

// INCLUDES

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

// STRUCTS FOR CONVENIANCE

typedef struct s_token
{
	int				index;
	char			*str;
	int				type;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	int				type;
	char			*heredoc;
	char			*file;
	char			*line;
	char			*tmp;
	int				herepipe[2];
	pid_t			herechild;
	int				fd;
	struct s_redir	*next;
}				t_redir;

typedef struct s_process
{
	struct s_process	*next;
	struct s_process	*prev;
	t_redir				*redirs;
	char				**cmd;
	char				*infile;
	char				*outfile;
	int					end[2];
	pid_t				child;
	int					file_in;
	int					file_out;
	int					heredocs;
	int					heredoc;
	int					piped;
}					t_process;

typedef struct s_minishell
{
	t_process		*process;
	t_token			*tokens;
	char			**tokenstab;
	char			**args;
	char			**envp;
	char			**paths;
	char			*line;
	int				status;
}		t_minishell;

// MANDATORY FCTS

char		*ft_read_line(int buff_size, int pos, int c);

//parsing

void		msh_get_tokens(t_minishell *msh, char *line);
int			ft_checkred(t_token *list);
void		msh_create_process(t_minishell *msh, t_token *lst);
int			msh_parse_redir(t_minishell *msh);
void		ft_heredocs(t_process *process);
void		ft_heredoc(t_redir *heredoc);

int			open_process_files(t_process *pipex);
void		exit_perror(char *error, int code);
int			close_files(t_process *pipex);

char		*ft_parsecmd(t_token *lst);
char		**msh_create_cmd(t_token *lst);
int			msh_count_cmd(t_token *lst);

// builtins

int			msh_echo(t_process *proc, t_minishell *msh);

int			msh_pwd(t_process *proc, t_minishell *msh);

void		msh_env(t_process *proc, t_minishell *msh);

int			msh_isbuiltin(char *cmd);
void		msh_execbuiltin(t_process *proc, t_minishell *msh);

int			msh_cd(t_process *proc, t_minishell *msh);

void		msh_exit(t_process *proc, t_minishell *msh);

void		msh_unset(t_process *proc, t_minishell *msh);

void		msh_export(t_process *proc, t_minishell *msh);
void		ft_sort_string_tab(char **tab);
char		*ft_strdupexport(char *src);
void		msh_printfexport(char **tab);
void		msh_export_noargs(t_minishell *msh);
char		**msh_realloc_env(t_minishell *msh, char *str);

// list utils

t_token		*ft_tokennew(char *str, int type, int index);
t_process	*ft_processnew(char **cmd, int piped, t_process *prev);
t_redir		*ft_redirnew(char *heredoc, int type, char *file);

void		ft_tokensclear(t_token **lst);
void		ft_redirsclear(t_redir **lst);
void		ft_processclear(t_process **lst);

void		ft_tokenadd_back(t_token **alst, t_token *new);
void		ft_rediradd_back(t_redir **alst, t_redir *new);
void		ft_processadd_back(t_process **alst, t_process *new);

void		ft_printtoken(t_token *list);
void		ft_printredirs(t_redir *list);
void		ft_printprocess(t_process *list);
void		ft_print_tab(char **tab);

// utils

char		*ft_strndup(char const *src, int n);
int			ft_len_alnum(char *str);
int			ft_lenquote(char *str);
int			ft_lendbquote(char *str);
void		ft_exit_fd(int fd, char *str);
char		*ft_realloc(char *str, int size);
int			ft_isprintsh(int c);
int			ft_isred(int c);
int			ft_istxt(int c);
int			ft_tablen(char **tab);
char		*ft_strcat(char *dest, char *src);
int			ft_len_total(int size, char **strs, char *sep);
char		*ft_tabjoin(int size, char **strs, char *sep);
int			ft_strcmp(char *str1, char *str2);
void		ft_free_tab(char **tab);
int			ft_tablen(char **tab);

// init

void		msh_init(t_minishell *msh, char **envp);

// exec

int		msh_execute(t_minishell *msh);

#endif