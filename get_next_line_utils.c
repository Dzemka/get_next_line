#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*(s++) != '\0')
		len++;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str_dup;

	if (!s1)
		return (NULL);
	i = 0;
	str_dup = NULL;
	while (s1[i])
		i++;
	str_dup = (char *)(malloc(sizeof(char) * i + 1));
	if (str_dup == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str_dup[i] = s1[i];
		i++;
	}
	str_dup[i] = '\0';
	return (str_dup);
}

char	*ft_strchr(const char *s, int c)
{
	char	*p;
	int		i;

	i = 0;
	p = (char *)s;
	while (p[i] != (char)c)
	{
		if (p[i] == '\0')
			return (NULL);
		i++;
	}
	return (p + i);
}

char	*ft_build_line(char *str1, char *str2, char *end_line)
{
	char	*new_str;
	size_t	len_new_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!str2)
		return (NULL);
	if (!str1)
		str1 = ft_strdup("");
	len_new_str = ft_strlen(str1) + ft_strlen(str2) + 1;
	new_str = malloc (len_new_str);
	if (end_line)
		*(end_line) = '\0';
	while (str1[j] != '\0')
		new_str[i++] = str1[j++];
	j = 0;
	while (str2[j] != '\0')
		new_str[i++] = str2[j++];
	new_str[i] = '\0';
	free (str1);
	return (new_str);
}
