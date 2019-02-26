/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 20:30:24 by wta               #+#    #+#             */
/*   Updated: 2019/02/26 13:26:05 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/includes/libft.h"
#include "rtv1.h"

t_node	*newnode(t_obj obj)
{
	t_node	*node;

	if ((node = ft_memalloc(sizeof(t_node))) != NULL)
	{
		node->next = NULL;
		node->obj = obj;
	}
	return (node);
}

void	pushback(t_lst *lst, t_node *node)
{
	if (lst != NULL && node != NULL)
	{
		if (lst->head == NULL)
			lst->head = node;
		else if (lst->tail == NULL)
		{
			lst->head->next = node;
			lst->tail = node;
		}
		else
		{
			lst->tail->next = node;
			lst->tail = node;
		}
	}
}
