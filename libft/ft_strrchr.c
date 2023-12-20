/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 20:08:53 by eagoumi           #+#    #+#             */
/*   Updated: 2022/11/08 20:35:39 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *ch, int s)
{
	size_t	i;

	i = ft_strlen(ch);
	while (i >= 0)
	{
		if (ch[i] == (char)s)
			return ((char *)&(ch[i]));
		if (i == 0)
			return (NULL);
		i--;
	}
	return (NULL);
}
