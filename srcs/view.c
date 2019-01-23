/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 22:02:07 by wta               #+#    #+#             */
/*   Updated: 2019/01/23 20:17:28 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>
#include "vectors.h"
#include "rtv1.h"

void	set_view(t_env *env)
{
	double	tan_half_angle;

	tan_half_angle = tan(env->scene.cam.fov / 2);
	env->scene.view.width = tan_half_angle * 2;
	env->scene.view.height = SCREEN_H / (SCREEN_W / env->scene.view.width);
	env->scene.view.dist = 1.;
}
