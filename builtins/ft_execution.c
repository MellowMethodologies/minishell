#include "minishell.h"

void ft_dup(t_parsed *lexe, int is_first, int count)
{
    int a_fd;
    int b_fd;
    if(is_first == 0)
    {
        if(count % 2 == 0)
        {
            b_fd = open("/tmp/b.txt", O_CREAT | O_RDWR, 0644);
            dup2(b_fd, 0);
        }
        else
        {
            a_fd = open("/tmp/a.txt", O_CREAT | O_RDWR, 0644);
            dup2(a_fd, 0);
        }
    }
    else if(lexe->in != -2 && lexe->in != 0)
        dup2(lexe->in, 0);
    if(lexe->next)
    {
        if(count % 2 == 0)
        {
            a_fd = open("/tmp/a.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
            dup2(a_fd, 1);
        }
        else
        {
            b_fd = open("/tmp/b.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
            dup2(b_fd, 1);
        }
    }
    else if(lexe->out != -2 && lexe->out != 1)
        dup2(lexe->out, 1);
}

char	**errs(char **env)
{
	char	**paths;

	paths = ft_split(ft_path(env), ':');
	return (paths);
}


void ft_execut_cmnd_one(t_parsed *lexe)
{
    char	**paths;
	char	*valid_path;

	paths = errs(lexe->envs);
	valid_path = ft_valid_path(paths, lexe->args[0]);
	if (valid_path == NULL)
	{
		write(2, "command not found\n", 18);
		exit(-1);
	}
	execve(valid_path, lexe->args, NULL);
	exit(50);
}

void ft_execut_cmnd(t_parsed *lexe, t_export **export)
{

    if(strcmp(lexe->args[0], "echo") == 0)
        ft_echo(lexe);
    else if(strcmp(lexe->args[0], "pwd") == 0)
        ft_pwd(lexe);
    else if(strcmp(lexe->args[0], "cd") == 0)
        ft_cd(lexe);
    else if(strcmp(lexe->args[0], "export") == 0)
        ft_export(lexe, export);
    else if(strcmp(lexe->args[0], "unset") == 0)
        ft_unset(lexe, export);
    else if(strcmp(lexe->args[0], "env") == 0)
        show_env(export, lexe);
    else if(strcmp(lexe->args[0], "exit") == 0)
    {
        exit(0);
    }
    else
        ft_execut_cmnd_one(lexe);
}

void    ft_cmnd(t_parsed *lexe, int count, int is_first, t_export **export)
{
    ft_dup(lexe, is_first, count);
    ft_execut_cmnd(lexe,export);
}

void    ft_execution(t_parsed *lexe, t_export **export, char **env)
{
    // write(2, "test\n", 5);
    int count = 0;
    int id = 0;
    pid_t status  = 100;
    if(lexe == NULL)
        return ;
    lexe->envs = env;
    id = fork();
    if(id == 0)
        ft_cmnd(lexe, count, 1,export);
    wait(&status);
    count++;
    lexe = lexe->next;
    while(lexe && lexe->next)
    {
        id = fork();
        if(id == 0)
        {
            lexe->envs = env;
            ft_cmnd(lexe, count, 0,export);
        }
        wait(&status);
        lexe = lexe->next;
        count++;
    }
    if(lexe)
    {
        id = fork();
        if(id == 0)
        {
            lexe->envs = env;
            ft_cmnd(lexe, count, 0, export);
        }
        wait(&status);
    }
    printf("statu = %d\n", WEXITSTATUS(status));
}