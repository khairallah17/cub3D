/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:36:10 by eagoumi           #+#    #+#             */
/*   Updated: 2022/11/08 20:33:23 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	lendest;
	size_t	lensrc;

	i = 0;
	j = 0;
	lendest = ft_strlen(dest);
	lensrc = ft_strlen(src);
	if (size != 0 && lendest < size)
	{
		while (i < lendest)
			i++;
		while (i < (lendest + lensrc) && i < (size - 1))
		{
			dest[i] = src[j];
			i++;
			j++;
		}
		dest[i] = '\0';
		return (lendest + lensrc);
	}
	return (lensrc + size);
}
