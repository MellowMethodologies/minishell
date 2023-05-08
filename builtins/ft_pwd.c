#include "../mini_shell.h"

void ft_pwd(t_parsed *lexe, t_export **export)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    }
    else
    {
        perror("getcwd() error");
        exit(1);
    }
    exit(0);
}
