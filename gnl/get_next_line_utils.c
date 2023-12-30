/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 18:46:05 by eagoumi           #+#    #+#             */
/*   Updated: 2022/12/18 18:46:05 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *string)
{
	int	count;

	count = 0;
	while (string[count] && string)
		count++;
	return (count);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*s2;

	s2 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (s2 == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

char	*join(char *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (s1 == NULL)
		return (ft_strdup(s2));
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	return (str);
}

char	*ft_strchr(const char *ch, int s)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = ft_strlen(ch);
	while (ch != 0 && i <= j)
	{
		if (ch[i] == (char )s)
			return ((char *)(ch + i));
		i++;
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*st;
	size_t	i;
	size_t	j;

	i = 0;
	if (!s || len == 0)
		return (ft_strdup(""));
	j = ft_strlen(s);
	if (j <= start)
		return (ft_strdup(""));
	if (len > j)
		len = j;
	st = (char *)malloc((len + 1) * sizeof(char));
	if (st == NULL)
		return (NULL);
	while (s[start + i] && i < len)
	{
		st[i] = s[start + i];
		i++;
	}
	st[i] = '\0';
	return (st);
}
