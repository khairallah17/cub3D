/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eagoumi <eagoumi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 01:45:58 by eagoumi           #+#    #+#             */
/*   Updated: 2022/11/08 20:26:04 by eagoumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*temporaire;

	temporaire = lst;
	if (temporaire)
	{
		while (temporaire->next)
		{
			temporaire = temporaire->next;
		}
		return (temporaire);
	}
	return (temporaire);
}
