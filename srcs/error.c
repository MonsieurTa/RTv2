/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:39:58 by wta               #+#    #+#             */
/*   Updated: 2019/01/25 16:44:46 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include "../libft/includes/libft.h"
#include "rtv1.h"

void	err_handler(int err_id)
{
	char	buf[255];

	ft_bzero(buf, 255);
	ft_strcpy(buf, "-Wolf3D: ");
	if (err_id == -1)
		ft_strcat(buf, strerror(errno));
	if (err_id == BAD_CMRDIR)
		ft_strcat(buf, "Bad camera direction");
	if (err_id == RD_ERR)
		ft_strcat(buf, "Read error");
	if (err_id == BAD_FMT || err_id == GNL_ERR)
		ft_strcat(buf, "Bad format");
	if (err_id == MALLOC_ERR)
		ft_strcat(buf, "Allocation failed");
	if (err_id == MLX_ERR)
		ft_strcat(buf, "Minilibx failure");
	ft_strcat(buf, "\n");
	if (err_id != 1)
		ft_putstr_fd(buf, 2);
	ft_putstr_fd("usage: wolf3d [map]\n", 2);
	exit(EXIT_FAILURE);
}
