/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 22:02:07 by wta               #+#    #+#             */
/*   Updated: 2019/01/22 02:12:05 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "vectors.h"
#include "rtv1.h"

void	set_view(t_info *info)
{
	double	tan_half_angle;

	tan_half_angle = tan(info->cam.fov / 2);
	info->view.width = tan_half_angle * 2;
	info->view.height = SCREEN_H / (SCREEN_W / info->view.width);
	info->view.dist = 1.;
}
