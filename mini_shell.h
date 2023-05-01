/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:53:47 by sbadr             #+#    #+#             */
/*   Updated: 2023/05/01 12:26:52 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINI_SHELL_H
# define MINI_SHELL_H

# include "./libft/libft.h"
# include <stdio.h>
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

extern struct	s_globvar
{
	int	sigquit;
}	t_glob;

//for the lexer part
typedef struct s_token{	
	int				type;
	int				dollars;
	char			*value;
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
	char			*cmd;
	char			**envs;
	int				in;
	int				out;
	struct s_parsed	*next;
}	t_parsed;

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
	t_export		*env;
	t_token			*lexe;
	t_token			*lex_without_spaces;
	t_parsed		*head;
	char			*res;
	char			*var;
	char			*value;
	char			**envs;
}	t_var;


char		*ft_quote_expander(char *str, t_export *env);
t_export	*ft_lstnew_export(void *var, char *value);
char		*ft_getenv(char *var, t_export *env);
int			check_type(t_token *lex);
char		*write_until(char *str, int c);
void		free_token(t_token *lst);
void		free_parsed(t_parsed *lst);
void		free_args(char **str);
int			special(int c);
int			calc_char(char *str, int c);
void		fill_export(t_export **exp, char **env);
int			check_quotes(char *line);
int			check_arguments(int c);
int			check_redirection(int c);
void		join_word_tokens(t_token *lex);
void		args_creation(t_parsed **cmd, t_token *tmp);
int			less_red(t_parsed **cmd, t_token **tmp);
int			great_red(t_parsed **cmd, t_token **tmp);
int			append_red(t_parsed **cmd, t_token **tmp);
int			heredoc_red(t_parsed **cmd, t_token **tmp, t_export *env);
t_token		*rm_space(t_token *lex);
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
void		ft_execution(t_parsed *lexe, t_export **export, char **env);
void		fill_export_with_1(t_export **export);
void		ft_expand(t_token *lexe, t_export *env);
void		ft_cd(t_parsed *lexe);
void		ft_echo(t_parsed *lexe);
void		ft_pwd(t_parsed *lexe);
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
void		show_export(t_export **export, t_parsed *lexe);
void		check_valide_args_for_export(char **strs);
int			arg_exist(char *str, t_export **export);
void		ft_join_value(t_export **export, char *str);
int			there_is_plus_equal(char *str);
void		ft_export(t_parsed *lexe, t_export **export);
void		ft_lst_delete_node_export(t_export **export, char *str);
void		ft_unset(t_parsed *lexe, t_export **export);
void		ft_execution(t_parsed *lexe, t_export **export, char **env);
char		*ft_path(char **str);
char		*ft_valid_path(char **paths, char *str);
void		ft_putstr(int fd, char *str);
int			word_len(const char *s, char c);
char		**str_count(char **str, const char *s, char c);
void		fill_export_with_1(t_export **export);
t_export	*ft_lstnew_texport_one();
#endif