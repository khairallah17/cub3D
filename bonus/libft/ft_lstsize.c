/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:21:17 by eagoumi           #+#    #+#             */
/*   Updated: 2022/11/08 20:38:36 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_lstsize(t_list *lst)
{
	int		count;
	t_list	*listtemp;

	count = 0;
	listtemp = lst;
	while (listtemp != NULL)
	{
		count++;
		listtemp = listtemp->next;
	}
	return (count);
}
