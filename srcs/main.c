/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:26:52 by wta               #+#    #+#             */
/*   Updated: 2019/01/22 01:27:54 by wta              ###   ########.fr       */
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

void	mlx_flow(t_info *info)
{
	if ((init_mlx(&info->mlx)) == 0)
		err_handler(MLX_ERR);
	render(&info->mlx.img, &info->cam, &info->view);
	mlx_put_image_to_window(info->mlx.mlx_ptr, info->mlx.win_ptr,
							info->mlx.img.img_ptr, 0, 0);
	mlx_hook(info->mlx.win_ptr, 2, 0, key_pressed, info);
	mlx_hook(info->mlx.win_ptr, 3, 0, key_released, info);
	mlx_hook(info->mlx.win_ptr, 17, 0, close_win, NULL);
	mlx_loop(info->mlx.mlx_ptr);
}

#include <stdio.h>

int	main(void)
{
	t_info	info;

	init_cam(&info.cam);
	set_view(&info);
	mlx_flow(&info);
	return (0);
}
