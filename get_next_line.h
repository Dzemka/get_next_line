#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *str, int c);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_build_line(char *str1, char *str2, char *end_line);

// # define BUFFER_SIZE 4		
typedef struct s_gnl
{
	char	*new_line;
	char	*end_line;
	char	*remaining_str;
}	t_gnl;
#endif
