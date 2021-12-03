#include "get_next_line.h"

static char	*ft_get_remaining(t_gnl *gnl, char *remaining_str)
{
	char	*temp_reamaining;

	temp_reamaining = NULL;
	if (!remaining_str)
		return (NULL);
	gnl->end_line = ft_strchr(remaining_str, '\n');
	if (gnl->end_line)
		if (*(++gnl->end_line) != '\0')
			temp_reamaining = ft_strdup(gnl->end_line);
	gnl->new_line = ft_build_line(gnl->new_line, remaining_str, gnl->end_line);
	free (remaining_str);
	return (temp_reamaining);
}

static char	*ft_get_res(int fd, char *buf, t_gnl *gnl)
{
	int			count_read;
	static char	*remaining_str;

	gnl->new_line = NULL;
	gnl->end_line = NULL;
	remaining_str = ft_get_remaining(gnl, remaining_str);
	while (!gnl->end_line)
	{
		count_read = read(fd, buf, BUFFER_SIZE);
		if (count_read == 0)
			break ;
		if (count_read == -1)
		{
			if (gnl->new_line)
				free (gnl->new_line);
			return (NULL);
		}
		buf[count_read] = '\0';
		gnl->end_line = ft_strchr(buf, '\n');
		if (gnl->end_line)
			if (*(++gnl->end_line) != '\0')
				remaining_str = ft_strdup(gnl->end_line);
		gnl->new_line = ft_build_line(gnl->new_line, buf, gnl->end_line);
	}
	return (gnl->new_line);
}

char	*get_next_line(int fd)
{
	t_gnl	*gnl;
	char	*buf;
	char	*res;

	res = NULL;
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	gnl = (t_gnl *)malloc(sizeof(t_gnl));
	if (buf && gnl)
		res = ft_get_res(fd, buf, gnl);
	if (gnl)
		free (gnl);
	if (buf)
		free (buf);
	return (res);
}
