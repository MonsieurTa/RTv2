/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:26:52 by wta               #+#    #+#             */
/*   Updated: 2019/01/29 22:41:35 by wta              ###   ########.fr       */
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
	env->key_pressed = 0;
	env->pxl = PIXEL;
	render(env);
	mlx_put_image_to_window(env->mlx.mlx_ptr, env->mlx.win_ptr, 
		env->mlx.img.img_ptr, 0, 0);
	mlx_hook(env->mlx.win_ptr, 2, 0, key_pressed, env);
	mlx_hook(env->mlx.win_ptr, 3, 0, key_released, env);
	mlx_hook(env->mlx.win_ptr, 17, 0, close_win, NULL);
	mlx_loop_hook(env->mlx.mlx_ptr, apply_key, env);
	mlx_loop(env->mlx.mlx_ptr);
}

#include <stdio.h>

int	main(void)
{
	t_env	env;

	init_cam(&env.cam);
	init_lst(&env.objs);
	init_lst(&env.lights);

	pushback(&env.objs, newnode(new_plane((t_v3){0., 0., 0.}, (t_v3){0.,0.,1.},
		(t_v3){50, 34., 120.}, (t_q){50, 0.2, 0.4, 0.3})));
	pushback(&env.objs, newnode(new_plane((t_v3){0., 50., 0.}, (t_v3){0.,-1.,0.},
		(t_v3){0, 0., 255.}, (t_q){50, 0.2, 0.4, 0.3})));
	pushback(&env.objs, newnode(new_sphere((t_v3){0., 0., 0.}, (t_v3){255., 0., 0.},
		1., (t_q){50, 0.2, 0.4, 0.3})));
	pushback(&env.objs, newnode(new_sphere((t_v3){5., 0., 0.}, (t_v3){0., 255., 0.},
		2., (t_q){50, 0.2, 0.4, 0.3})));
	pushback(&env.lights, newnode(new_light(AMBT_LIGHT, (t_v3){0., 0., 0.},
		(t_v3){255, 255., 255.}, (t_v3){0., 0.2, 0.})));
	pushback(&env.lights, newnode(new_light(SPHERE_LIGHT, (t_v3){0., -10., 0.},
		(t_v3){255, 255., 255.}, (t_v3){0., 0.6, 0.})));
	mlx_flow(&env);
	return (0);
}
