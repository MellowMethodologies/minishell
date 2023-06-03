/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isbarka <isbarka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:53:47 by sbadr             #+#    #+#             */
/*   Updated: 2023/06/03 15:11:34 by isbarka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "./libft/libft.h"
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <errno.h>
# include <termios.h>
# include <dirent.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>

# define PID -2
# define WHITESPACE -1
# define WORD 0
# define DOUBLE_QUOTE 1
# define SINGLE_QUOTE 2
# define PIPE 3
# define GREAT 4
# define LESS 5
# define GREATGREAT 44
# define HEREDOC 55
# define VAR 7
# define SYNTAX_ERROR 9

extern int	g_lobal;

//for the lexer part
typedef struct s_token{	
	int				type;
	int				ambiguous;
	char			*value;
	int				here_me;
	int				index;
	struct s_token	*next;
}	t_token;

typedef struct s_vars{
	int				fd_unlink;
	char			*fd[1024];
}	t_vars;

typedef struct s_parsed
{
	char			**args;
	int				args_null;
	int				error;
	char			*error_str;
	char			**envs;
	int				in;
	int				out;
	struct s_parsed	*next;
}	t_parsed;

//for the execution part
typedef struct s_ex_vars{	
	int			exit_status;
	int			count;
	int			id;
	int			start;
	int			end;
	int			i;
	pid_t		status;
	char		**env;
	int			stdin_;
	int			stdout_;
	int			save_prev_stdin;
	int			ss;
	t_parsed	*lexe;
	t_parsed	*first_lexe;
}	t_ex_vars;

typedef struct s_export
{
	char			*variable;
	char			*value;
	int				there_is_equal;
	struct s_export	*next;
}	t_export;

typedef struct s_var
{
	int				i;
	int				j;
	int				dollar_found;
	t_parsed		*cmd;
	t_parsed		*head;
	t_token			*lexe;
	t_token			*tmp;
	t_export		*env;
	t_token			*lex_without_spaces;
	char			*line;
	char			*temp;
	char			*result;
	char			*res;
	char			*var;
	char			*value;
	char			**envs;
}	t_var;

char		*ft_get_word(char *str, int *i);
int			args_count(t_token *lst);
void		ft_expand(t_token *lexe, t_export *env);
void		parsed_filler(t_parsed *cmd, t_token *l, \
t_parsed **h, t_export *env);
t_parsed	*ft_parse(char *str, t_export *env, t_var *vars);
int			check_syntax(t_token *tmp);
void		check_lex(t_parsed *head, t_token *lex);
void		free_tokens(t_token **lst);
char		*ft_quote_expander(char *str, t_export *env, int etat);
t_export	*ft_lstnew_export(void *var, char *value);
char		*ft_getenv(char *var, t_export *env);
int			check_type(t_token *lex);
char		*write_until(char *str, int c);
void		free_parsed(t_parsed **lst);
void		free_args(char **str);
int			special(int c);
int			calc_char(char *str, int c);
void		fill_export(t_export **exp, char **env);
int			check_quotes(char *line);
int			check_arguments(int c);
void		heredoc_handle(int sig);
int			check_redirection(int c);
void		join_word_tokens(t_token *lex);
void		args_creation(t_parsed **cmd, t_token *tmp);
void		args_creation(t_parsed **cmd, t_token *tmp);
void		less_red(t_parsed *cmd, t_token *tmp);
void		great_red(t_parsed *cmd, t_token *tmp);
void		append_red(t_parsed *cmd, t_token *tmp);
void		heredoc_red(t_parsed *cmd, t_token *tmp, t_export *env);
void		rm_space(t_token **lex);
t_token		*find_node(t_token *lex, int index);
t_token		*ft_lstne(void *value, int type);
t_token		*lexer(char *str, t_export *env);
void		add_back_parsed(t_parsed **lst, t_parsed *new);
int			ft_count(char const *s, char c);
size_t		ft_strlen(const char *str);
int			find_me(char *str, int endquot, int stat);
void		add_back(t_token **lst, t_token *new);
void		indexer(t_token **lex);
void		ft_lstadd_back_texport(t_export **lst, t_export *new);
void		ft_lstadd_back_tparsed(t_parsed **lst, t_parsed *new);
void		ft_execution(t_parsed *lexe, t_export **export);
void		fill_export_with_1(t_export **export);
void		ft_expand(t_token *lexe, t_export *env);
void		ft_cd(t_parsed *lexe, t_export **export);
void		ft_echo(t_parsed *lexe);
void		ft_lstdelone_texport(t_export *lst);
void		ft_lstdelone_tparsed(t_parsed *lst);
void		ft_lstadd_back_texport(t_export **lst, t_export *new);
void		ft_lstadd_back_tparsed(t_parsed **lst, t_parsed *new);
t_export	*ft_lstnew_texport(char *str);
void		fill_export_with_env(t_export *export, t_parsed *lexe);
char		*str_after_equal(char *str, int there_is_equal);
char		*str_befor_equal(char *str, int there_is_equal);
int			check_char_is_exist(char *str);
void		show_env(t_export **export, t_parsed *lexe);
void		check_valide_args_for_export(char **strs);
int			arg_exist(char *str, t_export **export);
void		ft_join_value(t_export **export, char *str);
int			there_is_plus_equal(char *str);
void		ft_export(t_parsed *lexe, t_export **export);
void		ft_lst_delete_node_export(t_export **export, char *str);
void		ft_unset(t_parsed *lexe, t_export **export);
char		*ft_path(char **str);
char		*ft_valid_path(char **paths, char *str);
void		ft_putstr(int fd, char *str);
int			word_len(const char *s, char c);
char		**str_count(char **str, const char *s, char c);
void		fill_export_with_1(t_export **export);
t_export	*ft_lstnew_texport_one(void);
int			find_me(char *str, int endquot, int stat);
int			special(int c);
void		check_for_quotes(t_token **lex, char *str, int *i);
int			check_for_specials(t_token **lex, char *str, int *i, int c);
void		check_words(t_token **lex, char *str, int *i, int here);
void		space_it(t_token **lex, char *str, int *i);
void		ft_change_exit_st(t_export **export, int exit_statu);
void		rl_replace_line(const char *text, int clear_undo);
void		handler(int sig);
void		ft_lstadd_back_texport(t_export **lst, t_export *new);
void		ft_lstadd_back_tparsed(t_parsed **lst, t_parsed *new);
void		fill_export_with_1(t_export **export);
void		ft_expand(t_token *lexe, t_export *env);
void		ft_cd(t_parsed *lexe, t_export **export);
void		ft_echo(t_parsed *lexe);
void		ft_pwd(void);
void		ft_lstdelone_texport(t_export *lst);
void		ft_lstdelone_tparsed(t_parsed *lst);
void		ft_lstadd_back_texport(t_export **lst, t_export *new);
void		ft_lstadd_back_tparsed(t_parsed **lst, t_parsed *new);
t_export	*ft_lstnew_texport(char *str);
void		fill_export_with_env(t_export *export, t_parsed *lexe);
char		*str_after_equal(char *str, int there_is_equal);
char		*str_befor_equal(char *str, int there_is_equal);
int			check_char_is_exist(char *str);
void		show_env(t_export **export, t_parsed *lexe);
void		show_export(t_export **export);
void		check_valide_args_for_export(char **strs);
int			arg_exist(char *str, t_export **export);
void		ft_join_value(t_export **export, char *str);
int			there_is_plus_equal(char *str);
void		ft_export(t_parsed *lexe, t_export **export);
void		ft_lst_delete_node_export(t_export **export, char *str);
void		ft_unset(t_parsed *lexe, t_export **export);
char		*ft_path(char **str);
char		*ft_valid_path(char **paths, char *str);
void		ft_putstr(int fd, char *str);
int			word_len(const char *s, char c);
char		**str_count(char **str, const char *s, char c);
void		fill_export_with_1(t_export **export);
t_export	*ft_lstnew_texport_one(void);
int			find_me(char *str, int endquot, int stat);
void		check_for_quotes(t_token **lex, char *str, int *i);
int			check_for_specials(t_token **lex, char *str, int *i, int c);
void		check_words(t_token **lex, char *str, int *i, int here);
void		space_it(t_token **lex, char *str, int *i);
void		ft_change_exit_st(t_export **export, int exit_statu);
void		rl_replace_line(const char *text, int clear_undo);
void		ft_dup_1(int is_first, int *fd, int count, t_parsed *lexe);
void		ft_dup(t_parsed *lexe, int is_first, int count);
char		**errs(char *env);
void		ft_execut_cmnd_one(t_parsed *lexe, t_export **export);
void		ft_execut_cmnd(t_parsed *lexe, t_export **export, t_ex_vars **v);
void		ft_cmnd(t_parsed *lexe, int count, int is_first, t_export **export);
void		ft_cmnd_one(t_parsed *lexe, t_export **ex);
void		fill_export_with_1(t_export **export);
void		ft_change_exit_st(t_export **export, int exit_statu);
void		ft_execution_5(t_ex_vars **ex_vars, t_parsed *lexe, t_export **ex);
void		ft_execution_3(t_parsed *lexe, t_export **ex, t_ex_vars **ex_vars);
void		ft_execution_2(t_parsed *lexe, t_export **ex, t_ex_vars **ex_vars);
void		ft_instantiate_ex_vars(t_ex_vars **ex_vars, char **env);
void		ft_exit_1( t_parsed **tmp, int i);
void		ft_exit(t_parsed *lexe1, t_ex_vars **v);
void		ft_execution_4( t_ex_vars **ex_vars, t_export **ex);
void		ft_print_strs(t_export **tmp);
void		show_env(t_export **export, t_parsed *lexe);
int			ft_equal(char *str, t_export **export);
int			plus_equal(char *str);
int			ft_just_equal(char *str);
void		ft_add_value_ft(char *str, t_export **export);
void		make_value_null(char *str, t_export **export);
void		ft_add_value(char *str, t_export **export);
void		ft_export_one(t_parsed *lexe, int i, t_export **ex, int is_eq);
void		ft_export(t_parsed *lexe, t_export **export);
int			there_is_plus_equal(char *str);
void		ft_join_value(t_export **export, char *str);
int			arg_exist(char *str, t_export **export);
void		show_export_1(t_export **tmp);
int			there_already(char *str1, t_export **export);
void		ft_add_variable(char *str, t_export **export);
int			error_var_1(char *str, int count);
int			error_var(char *str);
int			there_is_equal(char *str);
void		fill_export_with_1(t_export **export);
void		ft_change_exit_st(t_export **export, int exit_statu);
void		ignor_lexe(t_parsed **lexe);
void		ft_execution_v1(t_parsed *l, t_export **ex, t_ex_vars v, int *fd);
void		ft_execution_v4(t_ex_vars *vars, int *fd);
void		ft_execution_v3(t_parsed **lexe, t_ex_vars *vars);
void		ft_execution_v2(t_parsed *l, t_ex_vars *v, t_export **ex, int *fd);
void		ft_execution_v5(t_parsed *l, t_ex_vars *v, t_export **ex, int *fd);
void		hundle_2(int a);
void		hundle_1(int a);
void		ft_instantiate_export(t_export **export);
int			exit_ww(char *s1, char *s2);
void		ft_show_args( t_parsed *lexe);
void		exit_(t_export **export, pid_t id, t_parsed *lexe1);
int			check_builtins(char **strs);

#endif
