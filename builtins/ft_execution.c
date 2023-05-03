#include "../mini_shell.h"

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

void    ft_cmnd_one(t_parsed *lexe, int count, int is_first, t_export **export)
{
    ft_execut_cmnd(lexe,export);
}

void fill_export_with_1(t_export **export)
{
    t_export *tmp = (*export);
    while(tmp)
    {
        tmp->there_is_equal = 1;
        tmp = tmp->next;
    }
}

void ft_change_exit_st(t_export **export, int exit_statu)
{
    t_export *tmp = (*export);
    while(tmp && strcmp(tmp->variable, "?") != 0)
        tmp = tmp->next;
    tmp->value = ft_itoa(exit_statu);
}

void    ft_execution(t_parsed *lexe_1, t_export **export, char **env)
{
    write(2, "tttt\n", 5);
    t_parsed *lexe = lexe_1;
    int exit_status = 0;
    int count = 0;
    int id = 0;
    pid_t status  = 100;
    if(lexe == NULL)
        return ;
    lexe->envs = env;
    if((strcmp(lexe->args[0], "export") == 0 && lexe->args[1] != NULL) || strcmp(lexe->args[0], "unset") == 0)
        ft_cmnd_one(lexe, count, 1,export);
    else
    {
        id = fork();
        if(id == 0)
            ft_cmnd(lexe, count, 1,export);
        wait(&status);
    }
    count++;
    lexe = lexe->next;
    while(lexe && lexe->next)
    {
        if((strcmp(lexe->args[0], "export") == 0 && lexe->args[1] != NULL) || strcmp(lexe->args[0], "unset") == 0)
            ft_cmnd_one(lexe, count, 0,export);
        else
        {
            id = fork();
            if(id == 0)
            {
                lexe->envs = env;
                ft_cmnd(lexe, count, 0,export);
            }
            wait(&status);
        }
        lexe = lexe->next;
        count++;
    }
    write(2, "test\n", 5);
    if(lexe)
    {
        if((strcmp(lexe->args[0], "export") == 0 && lexe->args[1] != NULL) || strcmp(lexe->args[0], "unset") == 0)
            ft_cmnd_one(lexe, count, 0, export);
        else
        {
        id = fork();
        if(id == 0)
        {
            lexe->envs = env;
            ft_cmnd(lexe, count, 0, export);
        }
        wait(&status);
        }
    }
    exit_status = WEXITSTATUS(status);
    ft_change_exit_st(export, exit_status);
}