/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 03:29:54 by eagoumi           #+#    #+#             */
/*   Updated: 2022/11/09 17:44:31 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*srcp;
	unsigned char	*srcp1;
	size_t			i;

	srcp = (unsigned char *) s1;
	srcp1 = (unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (srcp[i] != srcp1[i])
			return ((srcp[i] - srcp1[i]));
		i++;
	}
	return (0);
}
