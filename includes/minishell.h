/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seujeon <seujeon@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 15:22:50 by seujeon           #+#    #+#             */
/*   Updated: 2022/04/07 10:41:15 by seujeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>

# include "libft.h"
# include "tree.h"
# include "error.h"

# define STDIN			0
# define STDOUT			1
# define STDERR			2

# define SW_WORD		0
# define SW_RDRL		1
# define SW_RDRR		2
# define SW_INDX		3
# define SW_RDSW		4

# define T_PIPE			0
# define T_COMD			1
# define T_REDS			2
# define T_WORD			3
# define T_REDR			4

# define TRUE			1
# define FALSE			0

# define MAX_DIRLEN		1024

# define PREFIX_EXPORT "declare -x "

# define SQUOTE			1
# define DQUOTE			2

# define DEFAULT		0
# define HERE_DOC		1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

int	g_exit_status;

typedef struct s_buffer
{
	char	*arr;
	size_t	size;
}				t_buffer;

enum e_intaryvar
{
	idx_str0,
	idx_str1,
	sw,
	indx,
	squote,
	dquote
};

typedef struct s_args
{
	size_t	cnt_space;
	int		flag_sq;
	int		flag_bq;
}				t_args;

typedef struct s_data
{
	char	**envp;
	int		syntax;
	int		pipecnt;
	int		pipeflag;
	int		wordcnt;
	int		roe_flag;
	int		tmp;
	char	*home;
}				t_data;

typedef struct s_fdargs
{
	int	fd1;
	int	fd2;
	int	argc;
}				t_fdargs;

typedef struct s_tokenidx
{
	int	i;
	int	j;
	int	sw;
}				t_tokenidx;
/*
** signal.c
*/
void		handle_signal(int signo);
void		ignore_sig(int signo);
void		ignore_signal(void (*handler)(int));
void		init_signal(void (*handler)(int));

/*
** signal2.c
*/
void		heredoc_signal(int signo);
int			handle_endline(char *line);

/*
** input_cmd.c
*/
char		*get_cmd(char **buf);
/*
** chk_input.c
*/
int			pre_process_input(char *str);
/*
** divide_parse.c
*/
void		divide_pipe(t_binode *parent, t_data *data);
void		divide_command(t_binode *parent, t_data *data);
void		divide_redirect(t_binode *parent);
/*
** parse_util.c
*/
int			ispipe(char c);
int			isword(char c);
int			isredirects(char c);
char		**calloc_redirects(size_t cnt);
/*
** parse_util2.c
*/
int			is_single_quotmark(char c);
int			is_double_quotmark(char c);
int			is_dollar_sign(char c);
int			is_space(char c);
char		*interprete_dollar_sign(char *str, int *size, char **envp);
int			correct_env(char *env, char *str, int size);
/*
** split_str.c
*/
char		**split_pipe(char *str, t_data *data);
char		**split_command(char *str);
char		**split_redirect(char *str);
/*
** execute.c
*/
void		execute(t_binode *tree, t_data *data);
void		execute_redr(t_binode *parent, t_data *data);
void		execute_word(t_binode *parent, t_data *data);
/*
** lexer.c
*/
void		divide_str(int divide_kind, t_binode *parent, t_data *data);
void		recur_parse(t_binode *parent, t_data *data);
t_binode	*parsetree(char *str, t_data *data);

/*
** pipex_util.c
*/
void		here_doc_child(int *fd, char *limit, t_data *data);
char		*find_path(char **envp, char *cmd);
char		**split_path(char **envp);

/*
** init_data.c
*/
void		init_data(t_data *data);
void		init_set(t_data *data, char **envp);

/*
** syntax.c
*/
void		syntax_redr(t_binode *node, t_data *data);
void		syntax_word(t_binode *node, t_data *data);

/*
** replace_dollersign.c
*/
char		*replace_dollar_sign(char *str, char **envp);

/*
** pipex.c
*/
void		new_process(char *cmd, t_data *data);
void		child_process(char *cmd, t_data *data);
void		open_fd_with_type(char *redr, char *file, t_data *data);

/*
** pipex_util2.c
*/
void		here_doc(char *limit, t_data *data);
void		action_parent(int *fd);
void		right_redr(int *fd, char *file, t_data *data);
void		left_redr(int *fd, char *file, t_data *data);

/*
** buffer.c
*/
int			init_buffer(t_buffer *buffer, size_t size);
void		flush_buffer(t_buffer *buffer, char **arr);
void		add_new_line_to_buffer(char **buffer, char *str);
/*
** replace_dollar_sign.c
*/
int			combine_variable(char **arr, char *str, char **envp);
void		ignore_single_quote(char *str, int *idx, t_buffer *buff);
char		*replace_dollar_sign(char *str, char **envp);
/*
** cmd_tokenizer.c
*/
int			token_cnt(char const *s, char c);
char		**cmd_tokenizer(char *str);
void		init_tokenidx(t_tokenidx *idx);
int			count_space(char *str);
/*
** cmd_tokenizer2.c
*/
int			jump_space(char *str, char **arr, t_buffer *buff, t_tokenidx *idx);
int			switch_ctrl(int	sw, char c);
void		put_buffer(t_buffer *buff, char c, int sw);
/*
** pt_exit.c
*/
int			pt_exit(char **cmd, int pipeflag);

/*
** executor/switch_routine.c
*/
int			switch_routine(char **new_argv, t_data *data);
/*
** pt_env.c
*/
int			pt_env(char **envp, char *prefix, char **new_argv);
/*
** pt_export.c
*/
int			pt_export(char ***envp, char **new_argv);
char		**realloc_env(int env_idx, char ***envp);
int			get_env_var(char *key, char **envp);
void		add_env(char ***envp, char *new_argv);

/*
** prt_image.c
*/
void		prt_image(void);
/*
** pt_cd.c
*/
int			pt_cd(char **argv, t_data *data);
char		*find_home(char *str, char **envp);

/*
** pt_unset.c
*/
int			pt_unset(char ***envp, char **new_argv);
int			is_valid_key(char *key);

/*
** pt_pwd.c
*/
int			pt_pwd(void);
/*
** pt_echo.c
*/
int			pt_echo(char **new_argv);
/*
** pt_exit_status.c
*/
int			pt_exit_status(char *str);
void		print_pipe_exit(int pipeflag);
int			print_execute_err_2(char *token1, char *token2, char *err_msg);
int			print_execute_err_1(char *token, char *err_msg, int pipeflag);
int			print_execute_err_3(char *head, char *token, char *err_msg);

#endif
