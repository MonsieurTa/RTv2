/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_rtv1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:53:32 by wta               #+#    #+#             */
/*   Updated: 2019/03/02 18:43:48 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"

void	lst_destroy(t_lst *lst)
{
	t_node	*node;
	t_node	*tmp;

	node = lst->head;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free(tmp);
	}
	lst->head = NULL;
	lst->tail = NULL;
}
