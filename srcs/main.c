/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:26:52 by wta               #+#    #+#             */
/*   Updated: 2019/01/24 03:52:58 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mlx.h"
#include "rtv1.h"

int	init_mlx(t_mlx *mlx)
{
	if (!(mlx->mlx_ptr = mlx_init()))
		return (0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SCREEN_W, SCREEN_H, "RTv1");
	if (!(mlx->win_ptr))
		return (0);
	if (!(mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, SCREEN_W, SCREEN_H)))
		return (0);
	if (!(mlx->img.img_str = (int*)mlx_get_data_addr(mlx->img.img_ptr,
							&mlx->img.bpp, &mlx->img.sizel, &mlx->img.endian)))
		return (0);
	return (1);
}

void	mlx_flow(t_env *env)
{
	if ((init_mlx(&env->mlx)) == 0)
		err_handler(MLX_ERR);
	render(&env->mlx, &env->scene);
	mlx_put_image_to_window(env->mlx.mlx_ptr, env->mlx.win_ptr,
							env->mlx.img.img_ptr, 0, 0);
	mlx_hook(env->mlx.win_ptr, 2, 0, key_pressed, env);
	mlx_hook(env->mlx.win_ptr, 3, 0, key_released, env);
	mlx_hook(env->mlx.win_ptr, 17, 0, close_win, NULL);
	mlx_loop(env->mlx.mlx_ptr);
}

#include <stdio.h>

int	main(void)
{
	t_env	env;

	init_cam(&env.scene.cam);
	init_lst(&env.scene.objs);
	set_view(&env);
	pushback(&env.scene.objs, newnode(new_sphere((t_vec3){0., 0., 0.}, 1., (t_color){255,0,0})));
	pushback(&env.scene.objs, newnode(new_sphere((t_vec3){5., 0., 0.}, 2., (t_color){0,255,0})));
	pushback(&env.scene.objs, newnode(new_sphere((t_vec3){-5., 0., 0.}, 2., (t_color){0,0,255})));
	pushback(&env.scene.objs, newnode(new_sphere((t_vec3){1., 3., -3.}, 1., (t_color){0,120,255})));
	pushback(&env.scene.objs, newnode(new_sphere((t_vec3){1., 1., -3.}, 1., (t_color){34,140,30})));
	pushback(&env.scene.objs, newnode(new_sphere((t_vec3){5., 3., -2.}, 1., (t_color){134,12,40})));
	pushback(&env.scene.objs, newnode(new_plane((t_vec3){0., 0., 0.}, (t_vec3){0.,-1.,0.}, (t_color){255,0.,0.})));
	pushback(&env.scene.lights, newnode(new_light((t_vec3){0., 0., 0.}, 0.2, DST_LIGHT, (t_color){0,0,255})));
	pushback(&env.scene.lights, newnode(new_light((t_vec3){-10., 10., -10.}, 0.4, SPHERE_LIGHT, (t_color){0,0,255})));
	pushback(&env.scene.lights, newnode(new_light((t_vec3){10., 10., -10.}, 0.4, SPHERE_LIGHT, (t_color){0,0,255})));
	mlx_flow(&env);
	return (0);
}
