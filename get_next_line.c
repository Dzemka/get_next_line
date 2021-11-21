#include "get_next_line.h"

static char *ft_join_and_free(char *str1, char *str2, char *end_line)
{
	char *new_str;
	
	if (!str1)
		str1 = ft_strdup("");
	if (end_line)
	{
		*(end_line) = '\0';
	}
	new_str = ft_strjoin(str1, str2);
	free(str1);
	return (new_str);
}

char *get_line(int fd, char *buf, char *new_line, char *end_line)
{
	int			count_read;
	static char *remaining_str;
	char 		*temp_remaining;
//	static int i;

//	i++;
	temp_remaining = NULL;
//	printf("%d", i);
//	printf("\n<==r:%s==>\n", remaining_str);
	if(remaining_str)
	{
		if((end_line = ft_strchr(remaining_str, '\n')))
		{
			if(*(++end_line) != '\0')
			temp_remaining = ft_strdup(end_line);
		}
		new_line = ft_join_and_free(new_line, remaining_str, end_line);
		free(remaining_str);
		remaining_str = ft_strdup(temp_remaining);
//		printf("\n<==t_r%s==>\n", temp_remaining);
		free(temp_remaining);
	}
//	printf("\n<==r2:%s==>\n", remaining_str);
//	printf("\n<==n_w:%s==>\n", new_line);
	while (!end_line && (count_read = read(fd, buf, BUFFER_SIZE)))
	{
		if (count_read < 1)
			return (NULL);
		buf[count_read] = '\0';
		if ((end_line = (ft_strchr(buf, '\n'))))
		{
			if (*(++end_line) != '\0')
				remaining_str = ft_strdup(end_line);
			else
				remaining_str = NULL;
		}
		new_line = ft_join_and_free(new_line, buf, end_line);
	}
	return(new_line);
}

char	*get_next_line(fd)
{
	char		*new_line;
	char		*end_line;
	char		*buf;
	
	if(fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	new_line = NULL;
	end_line = NULL;
	buf = malloc(BUFFER_SIZE + 1);
	new_line = get_line(fd, buf, new_line, end_line);
	free(buf);
	return (new_line);
}

//int main()
//{
//	int		fd;
//	int		i;
//	char	*res;
//
//	i = 1;
//	fd = open("text.txt", O_RDONLY);
//
//	while (i <= 11)
//	{
//		res = get_next_line(fd);
//		printf(".%d-%s", i, res);
//		i++;
//	}
//}
