/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:42:00 by wta               #+#    #+#             */
/*   Updated: 2019/01/23 20:14:34 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"

int			key_pressed(int key, void *param)
{
	t_env	*env;

	(void)key;
	env = (t_env*)param;
	if (key == ESC)
		exit(0);
	return (0);
}

int			key_released(int key, void *param)
{
	t_env	*env;

	(void)key;
	env = (t_env*)param;
	return (0);
}

int			close_win(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}
