/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 03:32:36 by eagoumi           #+#    #+#             */
/*   Updated: 2022/11/08 20:32:23 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

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
