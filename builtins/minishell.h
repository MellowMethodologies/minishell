#ifndef MINISHELL_H
#define MINISHELL_H
    
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <limits.h>
    #include <fcntl.h>
    #include "../libft/libft.h"
    #include <unistd.h>

typedef struct s_parsed
{
    struct s_parsed    *next;
    char        **args;
    char        *cmd;
    char        **envs;
    int         in;
    int         out;
    int         exit_statu;
}   t_parsed;


typedef struct s_export
{
    struct s_export    *next;
    char        *variable;
    char        *value;
    int        there_is_equal;
    
}   t_export;

    
char	*ft_strdup(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
void ft_cd(t_parsed *lexe);
void ft_echo(t_parsed *lexe);
void ft_pwd(t_parsed *lexe);
char	**ft_split(const char *s, char c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_bzero(void *s, size_t n);
void	ft_lstdelone_texport(t_export *lst);
void	ft_lstdelone_tparsed(t_parsed *lst);
void	ft_lstadd_back_texport(t_export **lst, t_export *new);
void	ft_lstadd_back_tparsed(t_parsed **lst, t_parsed *new);
t_export	*ft_lstnew_texport(char *str);
void fill_export_with_env(t_export *export, t_parsed *lexe);
char *str_after_equal(char *str, int there_is_equal);
char *str_befor_equal(char *str, int there_is_equal);
int check_char_is_exist(char *str);
void show_env(t_export **export, t_parsed *lexe);
void show_export(t_export **export, t_parsed *lexe);
void check_valide_args_for_export(char **strs);
int arg_exist(char *str, t_export **export);
void ft_join_value(t_export **export, char *str);
int there_is_plus_equal(char *str);
void ft_export(t_parsed *lexe, t_export **export);
void ft_lst_delete_node_export(t_export **export, char *str);
void    ft_unset(t_parsed *lexe, t_export **export);
void    ft_execution(t_parsed *lexe, t_export **export, char **env);
char	**ft_split(const char *s, char c);
char	*ft_path(char **str);
char	*ft_valid_path(char **paths, char *str);
void	ft_putstr(int fd, char *str);
int	word_len(const char *s, char c);
char	**str_count(char **str, const char *s, char c);
t_export	*ft_lstnew_texport_one();
void fill_export_with_1(t_export **export);


#endif