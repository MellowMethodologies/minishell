#include "../mini_shell.h"

int check_char_is_exist(char *str)
{
    int i = 0;

    while(str[i])
    {
        if(str[i] == '=')
        {
            return 1;
        }
        i++;
    }
    return 0;
}

char *str_befor_equal(char *str, int there_is_equal)
{
    int i = 0;
    char *to_return;
    int count = 0;
    if(there_is_equal == 0)
        return (ft_strdup(str));
    while(str[count] && str[count] != '=' && str[count] != '+')
    {
        count++;
    }
    to_return = malloc(count + 1);
    while(str[i] && str[i] != '=' && str[i] != '+')
    {
        to_return[i] = str[i];
        i++;
    }
    to_return[i] = '\0';
    return to_return;
}

char *str_after_equal(char *str, int there_is_equal)
{
    int start = 0;
    int end = 0;
    int i = 0;
    char *to_return;
    if(there_is_equal == 0)
        return NULL;

    while(str[start] && str[start] != '=')
    {
        start++;
    }
    start++;
    while(str[end])
    {
        end++;
    }
    if(end - start == 0)
        return NULL;
    to_return = malloc(end - start + 1);
    while(str[start])
    {
        to_return[i] = str[start];
        start++;
        i++;
    }
    to_return[i] = '\0';
    return to_return;
}

void fill_export_with_env(t_export *export, t_parsed *lexe)
{
    t_export *tmp;
    export->there_is_equal = check_char_is_exist(lexe->envs[0]);
    export->variable = str_befor_equal(lexe->envs[0], export->there_is_equal);
    export->value = str_after_equal(lexe->envs[0], export->there_is_equal);

    int i = 1;
    export->next = NULL;
    while(lexe->envs[i])
    {
        ft_lstadd_back_texport(&export, ft_lstnew_texport_one());
        tmp = export;
        while(tmp->next)
            tmp = tmp->next;
        tmp->there_is_equal = check_char_is_exist(lexe->envs[i]);
        tmp->variable = str_befor_equal(lexe->envs[i], export->there_is_equal);
        tmp->value = str_after_equal(lexe->envs[i], export->there_is_equal);
        i++;
    }
}

void show_env(t_export **export, t_parsed *lexe)
{
    t_export *tmp = (*export);
    while(tmp)
    {
        if(tmp->there_is_equal == 0)
        {
        }
        else if (tmp->there_is_equal == 1 && tmp->value == NULL)
        {
            ft_putstr_fd(tmp->variable , 1);
            write(1, "=",2);
            write(1, "\n", 1);
        }
        else
        {
            ft_putstr_fd(tmp->variable , 1);
            ft_putstr_fd("=" , 1);
            ft_putstr_fd(tmp->value , 1);
            write(1, "\n", 1);
        } 
        tmp = tmp->next;
    }
    exit(0);
}