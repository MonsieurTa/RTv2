/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:26:52 by wta               #+#    #+#             */
/*   Updated: 2019/03/02 22:45:10 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "../libft/includes/libft.h"
#include "mlx.h"
#include "rtv1.h"

int		init_mlx(t_mlx *mlx)
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
	draw_all(env);
	mlx_put_image_to_window(env->mlx.mlx_ptr, env->mlx.win_ptr,
			env->mlx.img.img_ptr, 0, 0);
	mlx_hook(env->mlx.win_ptr, 2, (1L<<0), key_pressed, env);
	mlx_hook(env->mlx.win_ptr, 3, (1L<<1), key_released, env);
	mlx_hook(env->mlx.win_ptr, 17, (1L<<0), close_win, NULL);
	mlx_loop_hook(env->mlx.mlx_ptr, apply_key, env);
	mlx_loop(env->mlx.mlx_ptr);
}

void	err_handler(t_error id)
{
	char	buf[255];

	ft_bzero(buf, 255);
	ft_strcat(buf, "Terminated with error: ");
	if (id == ERR_ERRNO)
		ft_strcat(buf, strerror(errno));
	if (id == ERR_BADFMT)
		ft_strcat(buf, "Bad format");
	if (id == ERR_MALLOC)
		ft_strcat(buf, "Malloc failed");
	if (id == ERR_GNL)
		ft_strcat(buf, "GNL failed");
	ft_strcat(buf, "\n");
	write(2, buf, ft_strlen(buf));
}

int		main(int ac, char **av)
{
	t_error	id;
	t_env	env;

	id = ERR_NOERROR;
	if (ac == 2)
	{
		ft_bzero(&env, sizeof(t_env));
		init_cam(&env.cam);
		env.spt = SCREEN_H / MAX_THREAD;
		id = read_file(&env, av[1]);
		if ((id = read_file(&env, av[1])) == ERR_NOERROR)
			mlx_flow(&env);
		lst_destroy(&env.objs);
		lst_destroy(&env.lights);
	}
	else
		write(1, "RTv1: usage: ./rtv1 file\n", 25);
	if (id != ERR_NOERROR)
		err_handler(id);
	return (0);
}
