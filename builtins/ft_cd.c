#include "minishell.h"

void ft_go_home(char *home)
{
    char cwd[1024];
    if(chdir(home) != 0)
    {
        write(2, "error home path", 15);
        exit(1);
    }
    char *oldpwd = getenv("PWD");
    setenv("OLDPWD", oldpwd, 1);
    getcwd(cwd, 1024);
    setenv("PWD", cwd, 1);
}

void ft_go_direction(char *dir)
{
    char cwd[1024];
    if(chdir(dir) != 0)
    {
        write(2, "error dir path", 15);
        exit(1);
    }
    char *oldpwd = getenv("PWD");
    setenv("OLDPWD", oldpwd, 1);
    getcwd(cwd, 1024);
    setenv("PWD", cwd, 1);
}

void ft_cd(t_parsed *lexe)
{
    char *home = getenv("HOME");
    if(lexe->args[1] == NULL)
    {
        ft_go_home(home);
    }
    else
    {
        ft_go_direction(lexe->args[1]);
    }
}
