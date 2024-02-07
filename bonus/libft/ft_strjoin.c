/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:45:07 by eagoumi           #+#    #+#             */
/*   Updated: 2022/11/08 20:33:08 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1tlen;
	size_t	s2tlen;
	size_t	lstcsempty;
	char	*str;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1tlen = ft_strlen(s1);
	s2tlen = ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1tlen + s2tlen + 1));
	if (str == NULL)
		return (NULL);
	lstcsempty = ft_strlcpy(str, s1, (s1tlen + s2tlen + 1));
	ft_strlcpy(str + lstcsempty, s2, ((s1tlen + s2tlen + 1) - lstcsempty));
	return (str);
}
