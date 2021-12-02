#include "get_next_line_bonus.h"

static char *ft_get_remaining(t_gnl *gnl, char *remaining_str)
{
    if (!gnl || !remaining_str)
        return (NULL);
    gnl->end_line = ft_strchr(remaining_str, '\n');
    if (gnl->end_line)
        if (*(++gnl->end_line) != '\0')
            gnl->remaining_str = ft_strdup(gnl->end_line);
    gnl->new_line = ft_build_line(gnl->new_line, remaining_str, gnl->end_line);
    free (remaining_str);
    return (gnl->remaining_str);
}

static char *ft_get_res(int fd, char *buf, t_gnl *gnl, t_list *elem)
{
    int         count_read;

    gnl->new_line = NULL;
    gnl->end_line = NULL;
    gnl->remaining_str = NULL;
    elem->remaining_str = ft_get_remaining(gnl, elem->remaining_str);
    while (!gnl->end_line)
    {
        count_read = read(fd, buf, BUFFER_SIZE);
        if (count_read == 0)
            break ;
        if (count_read == -1)
            return (NULL);
        buf[count_read] = '\0';
        gnl->end_line = ft_strchr(buf, '\n');
        if (gnl->end_line)
            if (*(++gnl->end_line) != '\0')
                elem->remaining_str = ft_strdup(gnl->end_line);
        gnl->new_line = ft_build_line(gnl->new_line, buf, gnl->end_line);
    }
    return (gnl->new_line);
}

static t_list *ft_lst_new(int fd)
{

    t_list  *lst_new;

    lst_new = (t_list *)malloc(sizeof(t_list));
    if (!lst_new)
        return (NULL);
    lst_new->fd = fd;
    lst_new->remaining_str = NULL;
    lst_new->next = NULL;
    return (lst_new);
}

t_list  *ft_select_elem(t_list *list, int fd)
{
    t_list  *elem;

    elem = list;
    while(elem->fd != fd)
    {
        if (elem->fd != fd && elem->next == NULL)
            elem->next = ft_lst_new(fd);
        elem = elem->next;
    }
    return(elem);
}

t_list  *ft_lst_clr(t_list *list, t_list *elem)
{
    
    t_list  *temp;

    if(!list)
        return (NULL);
    if (list == elem)
    {
        list = list->next;
        free(elem);
    }
    else
    {
        temp = list;
        while (temp->next != elem)
            temp = temp->next;
        temp->next = elem->next;
        free(elem);
    }
    return(list);
}

char    *get_next_line(int fd)
{
    t_gnl   *gnl;
    char    *buf;
    char    *res;
    static  t_list  *list;
    t_list  *elem;

    if (fd < 0 || BUFFER_SIZE < 0)
        return (NULL);
    if(!list)
    {
        list = ft_lst_new(fd);
        elem = list;
    }
    else
        elem = ft_select_elem(list, fd);
    buf = malloc(BUFFER_SIZE + 1);
    if (!buf)
        return (NULL);
    gnl = (t_gnl *)malloc(sizeof(t_gnl) * (BUFFER_SIZE + 1));
    res = NULL;
    if (gnl)
    {
        res = ft_get_res(fd, buf, gnl, elem);
        free (gnl);
    }
    free (buf);
    if(elem->remaining_str == NULL)
        list = ft_lst_clr(list, elem);
    return (res);
}
