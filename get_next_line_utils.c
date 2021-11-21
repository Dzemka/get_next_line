#include "get_next_line.h"

size_t ft_strlen(const char *s)
{
	size_t len;
	
	len = 0;
	while (*(s++) != '\0')
		len++;
	return (len);
}

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	
	i = dstsize - 1;
	j = 0;
	if (dstsize != 0)
	{
		while (i > 0 && src[j] != '\0')
		{
			dst[j] = src[j];
			j++;
			i--;
		}
		dst[j] = '\0';
	}
	return (ft_strlen(src));
}

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	len_dst;
	size_t	len_src;
	
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (dstsize < len_dst)
		return (dstsize + len_src);
	else
		ft_strlcpy(dst + len_dst, src, (dstsize - len_dst));
	return (len_src + len_dst);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*str_dup;
	
	if(!s1)
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

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_new_str;
	char	*str;
	
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = NULL;
	len_new_str = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(char) * (len_new_str));
	if (str == NULL)
		return (NULL);
	(void)ft_strlcpy(str, s1, len_new_str);
	(void)ft_strlcat(str, s2, len_new_str);
	return (str);
}