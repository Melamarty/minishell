#include "../minishell.h"

void    ft_dup2(int fd1, int fd2)
{
    if (dup2(fd1, fd2) == -1)
        exit(1);
}

void print_list(t_list *list)
{
    while (list)
    {
        printf("token: %s\n", list->token);
        printf("fd: %d\n", list->fd);
        list = list->next;
    }
}

int file_error(char *file)
{
    write(2, "minishell: ", 11);
    write (2, file, ft_strlen(file));
    write (2, ": No such file or directory\n", 29);
    return (0);
}

int redirect_out(t_tree *tree, t_env **env)
{
    int fd;
    t_list *tmp;
    int cpy;

    tmp = tree->cmd->redir_out;
    while (tmp)
    {
        if (tmp->type)
            fd = open(tmp->token, O_CREAT | O_RDWR | O_APPEND, 0644);
        else
            fd = open(tmp->token, O_CREAT | O_RDWR | O_TRUNC, 0644);
        if (fd < 0)
            return (file_error(tmp->token));
        tmp->fd = fd;
        if (tmp->next)
            close(fd);
        tmp = tmp->next;
    }
    cpy = dup(1);
    ft_dup2(fd, 1);
    close(fd);
    if (tree->cmd->cmd)
        exec_cmd(tree->cmd, env);
    ft_dup2(cpy, 1);
    return (1);
}

int read_fd (int fd, t_env *env)
{
    int     res_fd;
    char    *buffer;
    char *name;

    name = ft_get_name();
    res_fd = open(".expand", O_RDWR | O_CREAT | O_TRUNC, 0644);
    int cpy = open(".expand", O_RDWR | O_CREAT | O_TRUNC, 0644);
    buffer = get_next_line(fd);
    while (buffer)
    {
        buffer[ft_strlen(buffer) - 1] = 0;
        // printf ("buffer before -%s-\n", buffer);
        buffer = ft_expand(buffer, env);
        write(res_fd, buffer, ft_strlen(buffer));
        // printf ("buffer is %s\n", buffer);
        buffer = get_next_line(fd);
        write (res_fd, "\n", 1);
    }
    return ( cpy);
}

int redirect_in(t_tree *tree, t_env **env)
{
    int fd;
    t_list *tmp;
    int cpy;

    tmp = tree->cmd->redir_in;
    while (tmp)
    {
        if (tmp->type == TOKEN_HEREDOC)
            fd = tmp->fd;
        else
            fd = open(tmp->token, O_RDONLY);
        if (fd < 0)
            return (file_error(tmp->token));
        tmp->fd = fd;
        if (tmp->next)
            close(fd);
        else
            break;
        tmp = tmp->next;
    }
    if (tmp->type == TOKEN_HEREDOC)
        fd = read_fd(tmp->fd, *env);
    cpy = dup(0);
    ft_dup2(fd, 0);
    close(fd);
    if (tree->cmd->cmd)
        exec_cmd(tree->cmd, env);
    ft_dup2(cpy, 0);
    return (0);
}

int redirect(t_tree *tree, t_env **env)
{
    t_list *list;

    if (tree->cmd->redir_in)
    {
        list = tree->cmd->redir_in;
        redirect_in(tree, env);
    }
    if (tree->cmd->redir_out)
    {
        list = tree->cmd->redir_out;
        redirect_out(tree, env);
    }
    return (1);
}