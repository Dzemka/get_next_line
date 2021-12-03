#include "get_next_line_bonus.h"

static t_list   *ft_clr_elem(t_list *list, t_list *elem)
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

t_list  *ft_select_elem(t_list *list, int fd)
{
    t_list  *elem;

    if (!list)
        return(NULL);
    elem = list;
    while(elem->fd != fd)
    {
        if (elem->fd != fd && !elem->next)
            elem->next = ft_lst_new(fd);
        elem = elem->next;
    }
    return(elem);
}

static char *ft_get_res(int fd, char *buf, t_gnl *gnl, t_list *elem)
{
    int         count_read;

    gnl->end_line = ft_strchr(elem->remaining_str, '\n');
    if (gnl->end_line)
        if (*(++gnl->end_line) != '\0')
            gnl->remaining_str = ft_strdup(gnl->end_line);
    gnl->new_line = ft_build_line(gnl->new_line, elem->remaining_str, gnl->end_line);
    free (elem->remaining_str);
    elem->remaining_str = gnl->remaining_str;
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
        list = ft_lst_new(fd);
    elem = ft_select_elem(list, fd);
    buf = malloc(BUFFER_SIZE + 1);
    gnl = (t_gnl *)malloc(sizeof(t_gnl) * (BUFFER_SIZE + 1));
    gnl->new_line = NULL;
    gnl->end_line = NULL;
    gnl->remaining_str = NULL;
    res = ft_get_res(fd, buf, gnl, elem);
    free (gnl);
    free (buf);
    if(elem->remaining_str == NULL)
        list = ft_clr_elem(list, elem);
    return (res);
}
