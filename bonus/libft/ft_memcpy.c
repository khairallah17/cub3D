/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:13:56 by eagoumi           #+#    #+#             */
/*   Updated: 2022/11/08 20:29:19 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*rgm;
	char	*rsrc;
	size_t	i;

	if (dst == NULL && src == NULL)
		return (NULL);
	rgm = dst;
	rsrc = (char *)src;
	i = 0;
	while (i < n)
	{
		rgm[i] = rsrc[i];
		i++;
	}
	return (rgm);
}
