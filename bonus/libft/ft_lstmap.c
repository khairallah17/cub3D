/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkhairal <mkhairal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 19:07:31 by eagoumi           #+#    #+#             */
/*   Updated: 2024/02/07 18:33:47 by mkhairal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

void	*del_free(t_list **lst, void (*del)(void *))
{
	ft_lstclear(lst, del);
	return (NULL);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_params	params;

	params.new_lst = NULL;
	while (f != NULL && del != NULL && lst != NULL)
	{
		params.new_content = f(lst->content);
		if (!params.new_content)
			return (del_free(&params.new_lst, del));
		params.new_node = ft_lstnew(params.new_content);
		if (!params.new_node)
			return (del_free(&params.new_lst, del));
		if (params.new_lst == NULL)
		{
			params.new_lst = params.new_node;
			params.last_node = params.new_lst;
		}
		else
		{
			params.last_node->next = params.new_node;
			params.last_node = params.last_node->next;
		}
		lst = lst->next;
	}
	return (params.new_lst);
}
