#include "minishell.h"

void ft_lst_delete_node_export(t_export **export, char *str)
{
    t_export *node_to_delete = (*export);
    t_export *previous_node = (*export);
    int check = 0;
    while(node_to_delete && strcmp(node_to_delete->variable, str) != 0)
    {
        if(check != 0)
            previous_node = previous_node->next;
        check = 1;
        node_to_delete = node_to_delete->next;
    }
    if(node_to_delete && node_to_delete->next)
        previous_node->next = node_to_delete->next;
    node_to_delete = NULL;
}


// int main(int ac, char **av, char **env)
// {
//     t_parsed    *lexe;
//     t_parsed    *lexe1;
//     t_parsed    *lexe2;
//     t_export    *export;
//     lexe = malloc(sizeof(t_parsed));
//     lexe1 = malloc(sizeof(t_parsed));
//     lexe2 = malloc(sizeof(t_parsed));
//     export = malloc(sizeof(t_export));
//     lexe->in = -2;
//     lexe1->in = -2;
//     lexe2->in = -2;
//     lexe->envs = env;
//     lexe1->envs = env;
//     lexe2->envs = env;
//     lexe->out = -2;
//     lexe1->out = -2;
//     lexe2->out = -2;
//     lexe->args = malloc(3 * sizeof(lexe->args));
//     lexe1->args = malloc(3 * sizeof(lexe->args));
//     lexe2->args = malloc(3 * sizeof(lexe->args));
//     lexe->args[0] = ft_strdup("ls");
//     lexe1->args[0] = ft_strdup("cat");
//     lexe2->args[0] = ft_strdup("env");
//     lexe->args[1] = NULL;
//     lexe1->args[1] = NULL;
//     lexe2->args[1] = NULL;
//     lexe->next = NULL;
//     lexe1->next = lexe2;
//     lexe2->next = NULL;
//     // fill_export_with_env(export, lexe);
//     ft_execution(lexe, &export);
//     exit(1);
//     ft_unset(lexe, &export);
//     show_env(&export, lexe);
//     lexe->next = NULL;
//     ft_cd(lexe);
// }