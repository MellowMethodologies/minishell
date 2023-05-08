#include "../mini_shell.h"

int there_already(char *str1, t_export **export)
{
    t_export *tmp = (*export);
    while(tmp)
    {
        if(strcmp(str1, tmp->variable) == 0)
        {
            return 1;
        }
        tmp = tmp->next;
    }
    return 0;
}

void ft_add_variable(char *str, t_export **export)
{
    
    char *str1 = str_befor_equal(str, 1);
    if(there_already(str1, export))
    {
        return ;
    }
    else
    {
        ft_lstadd_back_texport(export, ft_lstnew_texport(str1));
        t_export *tmp = (*export);
    }
}

int error_var(char *str)
{
    int count = 0;
    if((str[count] >= 'a' && str[count] <= 'z')
            || (str[count] >= 'A' && str[count] <= 'Z') ||
            str[count] == '_')
    {
    }
    else
        return 1;
    count++;
    while(str[count] && str[count] != '=' && str[count] != '+')
    {
        if((str[count] >= 'a' && str[count] <= 'z')
            || (str[count] >= 'A' && str[count] <= 'Z') || str[count] == '_'
            ||  (str[count] >= '0' && str[count] <= '9') )
        {
        }
        else
            return 1;
        count++;
    }
    if(str[count] && str[count] == '+')
    {
        if(str[count + 1] && str[count + 1] != '=')
            return 1;
    }
    return 0;
}

int there_is_equal(char *str)
{
    int i = 0;
    while (str[i])
    {
        if(str[i] == '=')
            return 1 ;
        i++;
    }
    return 0 ;
}

int ft_equal(char *str, t_export **export)
{
    t_export *tmp = (*export);

    while(tmp && strcmp(str_befor_equal(str,1), tmp->variable) != 0)
    {
        tmp = tmp->next;
    }
    if(there_is_equal(str))
    {
        tmp->there_is_equal = 1;
        return 1;
    }
    else
    {
        tmp->there_is_equal = 0;
        return 0;
    }
}

int plus_equal(char *str)
{
    int i = 0;
    while(str[i] && str[i + 1])
    {
        if(str[i] == '+' && str[i + 1] == '=')
            return 1;
        i++;   
    }
    return 0;
}

int ft_just_equal(char *str)
{
    int i = 0;
    while(str[i])
    {
        if(str[i] == '=')
            return 1;
        i++;   
    }
    return 0;
}


void ft_add_value_ft(char *str,t_export **export)
{
    t_export *tmp = (*export);
    while(tmp && strcmp(tmp->variable, str_befor_equal(str, 1)) != 0)
        tmp = tmp->next;
    tmp->value = str_after_equal(str,1);
}

void make_value_null(char *str, t_export **export)
{
    t_export *tmp = (*export);
    while(tmp && strcmp(tmp->variable, str_befor_equal(str,1)) != 0)
        tmp = tmp->next;
    tmp->value = NULL;
}

void ft_add_value(char *str, t_export **export, int there_is_equal)
{
    if(plus_equal(str))
    {
        ft_join_value(export, str);
    }
    else if(ft_just_equal(str))
    {  
        ft_add_value_ft(str, export);
    }
    else
        make_value_null(str, export);
}

void ft_export(t_parsed *lexe, t_export **export)
{
   int i = 1;
   int there_is_equal = -2;

    t_export *tmp = (*export);
    if(lexe->args[1] == NULL || strcmp(lexe->args[1], "") == 0)
    {
        show_export(export, lexe);
        exit(0);
    }
    else
    {
        while(lexe->args[i])
        {
            if(error_var(lexe->args[i]) == 1)
            {
                //remove this and don't exit in error
                write(2, "error input\n", 12);
                // exit(1);
            }
            else
            {
                
                ft_add_variable(lexe->args[i], export);
                there_is_equal = ft_equal(lexe->args[i], export);
                ft_add_value(lexe->args[i], export, there_is_equal);
                // t_export *tmp = (*export);
                // while(tmp)
                // {
                //     printf("%s\neqaul = %d\n", tmp->variable, tmp->there_is_equal);
                //     tmp = tmp->next;
                // }
            }
            i++;
        }
    }
}

int there_is_plus_equal(char *str)
{
    int i = 0;
    while(str[i + 1])
    {
        if(str[i] == '+' && str[i + 1] == '=')
        {
            return 1;
        }
        i++;
    }
    return 0;
}

void ft_join_value(t_export **export, char *str)
{
    t_export *tmp = (*export);
    while(tmp && strcmp(tmp->variable, str_befor_equal(str, 1)) != 0)
    {
        tmp = tmp->next;
    }
    tmp->value = ft_strjoin(tmp->value, str_after_equal(str, 1));
}

int arg_exist(char *str, t_export **export)
{
    t_export *tmp = (*export);
    while(tmp && strcmp(tmp->variable, str) != 0)
    {
        tmp = tmp->next;
    }
    if(!tmp)
        return 0;
    return 1;
}


void show_export(t_export **export, t_parsed *lexe)
{
    t_export *tmp = (*export);
    while(tmp)
    {
        if(strcmp(tmp->variable, "?") == 0)
            tmp = tmp->next;
        if(tmp && tmp->there_is_equal == 0)
        {
            ft_putstr_fd("declare -x " , 1);
            ft_putstr_fd(tmp->variable , 1);
            write(1, "\n", 1);
        }
        else if (tmp && tmp->there_is_equal == 1 && tmp->value == NULL)
        {
            ft_putstr_fd("declare -x " , 1);
            ft_putstr_fd(tmp->variable , 1);
            write(1, "=\"\"",4);
            write(1, "\n", 1);

        }
        else if (tmp)
        {
            ft_putstr_fd("declare -x " , 1);
            ft_putstr_fd(tmp->variable , 1);
            ft_putstr_fd("=" , 1);
            ft_putstr_fd("\"" , 1);
            ft_putstr_fd(tmp->value , 1);
            ft_putstr_fd("\"" , 1);
            write(1, "\n", 1);
        }
        if(tmp)
            tmp = tmp->next;
    }
}