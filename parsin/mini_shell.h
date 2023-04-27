/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_shell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbadr <sbadr@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 00:53:47 by sbadr             #+#    #+#             */
/*   Updated: 2023/04/27 18:40:07 by sbadr            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef _MINI_SHELL_H
# define _MINI_SHELL_H

#include "../libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <termios.h>
#include <dirent.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <curses.h>

#define WHITESPACE -1
#define WORD 0
#define DOUBLE_QUOTE 1
#define SINGLE_QUOTE 2
#define PIPE 3
#define GREAT 4
#define LESS 5
#define GREATGREAT 44
#define HEREDOC 55
#define VAR 7
#define SYNTAX_ERROR 9

//for the lexer part
typedef struct s_token{	
	int		type;
	char	*value;
	int		index;
	struct s_token *next;
} t_token;

typedef struct s_vars{
	int 	fd_unlink;
	char	*fd[1024];
} t_vars;

typedef struct s_parsed
{
	struct s_parsed    *next;
	char        **args;
	char        *cmd;
	char        **envs;
	int         in;
	int         out;
}   t_parsed;

typedef struct s_export
{
	struct s_export    *next;
	char        *variable;
	char        *value;
	int        there_is_equal;
}   t_export;

char        *ft_quote_expander(char *str, t_export *env);
t_export	*ft_lstnew_export(void *var, char* value);
char		*ft_getenv(char *var, t_export *env);
int			check_type(t_token *lex);
int			check(int x);
char        *write_until(char *str, int c);
void		free_token(t_token *lst);
void 		unlinker(t_vars var);
void		free_parsed(t_parsed *lst);
void		free_args(char **str);
int			special(int c);
int         calc_char(char *str, int c);
void        fill_export(t_export **exp, char **env);
int         check_quotes(char *line);
int         check_arguments(int c);
int         check_redirection(int c);
void        join_word_tokens(t_token *lex);
void		args_creation(t_parsed **cmd, t_token *tmp);
int		    less_red(t_parsed **cmd, t_token **tmp);
int		    great_red(t_parsed **cmd, t_token **tmp);
int 		append_red(t_parsed **cmd, t_token **tmp);
int 		heredoc_red(t_parsed **cmd, t_token **tmp, t_export *env);
t_token		*rm_space(t_token *lex);
t_token		*find_node(t_token *lex, int index);
t_token		*ft_lstne(void *value, int type);
t_token		*lexer(char *str, t_token *lex, t_export *env);
t_parsed	*ft_lstnew_parsed(char *value, char **arg,int in, int out);
void		add_back_parsed(t_parsed **lst, t_parsed *new);
int			ft_count(char const *s, char c);
size_t		ft_strlen(const char *str);
void		cd(char *str, char *home);
int 		find_me(char *str, int endquot, int stat);
void		add_back(t_token **lst, t_token *new);
void		indexer(t_token **lex);
void		ft_lstadd_back_texport(t_export **lst, t_export *new);
void		ft_lstadd_back_tparsed(t_parsed **lst, t_parsed *new);
void		ft_execution(t_parsed *lexe, t_export **export, char **env);
void		append_list(t_token** lst1, t_token **lst2);

#endif