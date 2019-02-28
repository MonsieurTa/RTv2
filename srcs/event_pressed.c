/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_pressed.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 01:34:38 by wta               #+#    #+#             */
/*   Updated: 2019/02/27 16:52:08 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"

void		arrow_pressed(int key, t_env *env)
{
	if (key == K_RIGHT)
		env->key_pressed |= 0x1;
	if (key == K_LEFT)
		env->key_pressed |= 0x2;
	if (key == K_UP)
		env->key_pressed |= 0x4;
	if (key == K_DOWN)
		env->key_pressed |= 0x8;
}

void		letter_pressed(int key, t_env *env)
{
	if (key == K_A)
		env->key_pressed |= 0x10;
	if (key == K_S)
		env->key_pressed |= 0x20;
	if (key == K_W)
		env->key_pressed |= 0x40;
	if (key == K_D)
		env->key_pressed |= 0x80;
	if (key == K_Q)
		env->key_pressed |= 0x100;
	if (key == K_E)
		env->key_pressed |= 0x200;
}

int			key_pressed(int key, void *param)
{
	t_env	*env;

	env = (t_env*)param;
	arrow_pressed(key, env);
	letter_pressed(key, env);
	if (key == NUM_ZERO)
	{
		env->shadow ^= 0x1;
		env->pxl = PIXEL;
	}
	if (key == K_PGUP)
		env->key_pressed |= 0x400;
	if (key == K_PGDOWN)
		env->key_pressed |= 0x800;
	if (key == ESC)
		exit(0);
	return (0);
}
