/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:42:00 by wta               #+#    #+#             */
/*   Updated: 2019/01/29 05:46:03 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"
#include "rtv1.h"

int			key_pressed(int key, void *param)
{
	t_env	*env;

	env = (t_env*)param;
	if (key == K_RIGHT)
		env->key_pressed |= 0x1;
	if (key == K_LEFT)
		env->key_pressed |= 0x2;
	if (key == K_UP)
		env->key_pressed |= 0x4;
	if (key == K_DOWN)
		env->key_pressed |= 0x8;
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
	if (key == K_O)
		env->key_pressed |= 0x400;
	if (key == K_I)
		env->key_pressed |= 0x800;
	if (key == ESC)
		exit(0);
	return (0);
}

int			key_released(int key, void *param)
{
	t_env	*env;

	env = (t_env*)param;
	if (key == K_RIGHT)
		env->key_pressed ^= 0x1;
	if (key == K_LEFT)
		env->key_pressed ^= 0x2;
	if (key == K_UP)
		env->key_pressed ^= 0x4;
	if (key == K_DOWN)
		env->key_pressed ^= 0x8;
	if (key == K_A)
		env->key_pressed ^= 0x10;
	if (key == K_S)
		env->key_pressed ^= 0x20;
	if (key == K_W)
		env->key_pressed ^= 0x40;
	if (key == K_D)
		env->key_pressed ^= 0x80;
	if (key == K_Q)
		env->key_pressed ^= 0x100;
	if (key == K_E)
		env->key_pressed ^= 0x200;
	if (key == K_O)
		env->key_pressed ^= 0x400;
	if (key == K_I)
		env->key_pressed ^= 0x800;
	return (0);
}

int			apply_key(void *param)
{
	t_env	*env;

	env = (t_env*)param;
	if (env->key_pressed != 0)
	{
		env->pxl = PIXEL;
		if (env->key_pressed & 0x1)
			env->cam.phi += 0.1;
		if (env->key_pressed & 0x2)
			env->cam.phi -= 0.1;
		if (env->key_pressed & 0x4)
			env->cam.theta -= 0.1;
		if (env->key_pressed & 0x8)
			env->cam.theta += 0.1;
		if (env->key_pressed & 0x10)
			env->cam.z_rot += 0.1;
		if (env->key_pressed & 0x80)
			env->cam.z_rot -= 0.1;
		if (env->key_pressed & 0x20)
			env->cam.x_rot -= 0.1;
		if (env->key_pressed & 0x40)
			env->cam.x_rot += 0.1;
		if (env->key_pressed & 0x200)
			env->cam.y_rot += 0.1;
		if (env->key_pressed & 0x100)
			env->cam.y_rot -= 0.1;
		if (env->key_pressed & 0x400)
			env->cam.r += 1.;
		if (env->key_pressed & 0x800)
			env->cam.r -= 1.;
	}
	env->pxl = (env->pxl > 0) ? env->pxl - 2 : env->pxl;
	if (env->pxl > 0)
	{
		compute_pos(&env->cam);
		render(env);
		mlx_put_image_to_window(env->mlx.mlx_ptr, env->mlx.win_ptr, 
			env->mlx.img.img_ptr, 0, 0);
	}
	return (0);
}

int			close_win(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}
