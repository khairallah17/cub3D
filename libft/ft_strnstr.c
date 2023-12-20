/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 02:19:04 by eagoumi           #+#    #+#             */
/*   Updated: 2022/10/19 02:19:04 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	i = 0;
	little_len = ft_strlen(little);
	if (!little_len)
		return ((char *)big);
	while (big[i] && i + little_len <= n)
	{
		if (big[i] == little[0])
		{
			j = 0;
			while (big[i + j] && little[j])
			{
				if (big[i + j] != little[j])
					break ;
				else if (j == little_len - 1)
					return ((char *)big + i);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
