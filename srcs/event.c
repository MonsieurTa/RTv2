/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:42:00 by wta               #+#    #+#             */
/*   Updated: 2019/01/21 13:48:18 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"

int			key_pressed(int key, void *param)
{
	t_info	*info;

	(void)key;
	info = (t_info*)param;
	if (key == ESC)
		exit(0);
	return (0);
}

int			key_released(int key, void *param)
{
	t_info	*info;

	(void)key;
	info = (t_info*)param;
	return (0);
}

int			close_win(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}
