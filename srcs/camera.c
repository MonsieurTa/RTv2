/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:52:13 by wta               #+#    #+#             */
/*   Updated: 2019/01/28 01:39:58 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vectors.h"
#include "rtv1.h"

#include<stdio.h>

void	check_dir(t_v3 dir)
{
	if (dir.x == 0. && dir.y == 0. && dir.z == 0)
		err_handler(BAD_CMRDIR);
	if (dir.x == 0. && dir.y == 0. && dir.z == 1.)
		err_handler(BAD_CMRDIR);
	if (dir.x == 0. && dir.y == 0. && dir.z == -1.)
		err_handler(BAD_CMRDIR);
}

void	spheric_to_cart(t_v3 *v, double r, double theta, double phi)
{
	v->x = r * sin(theta) * cos(phi);
	v->y = r * sin(theta) * sin(phi);
	v->z = r * cos(theta);
}

void	init_cam(t_cam *cam)
{
	cam->phi = -M_PI / 2;
	cam->theta = M_PI / 2.;
	cam->r = 1.;
	cam->x_rot = 0.;
	cam->y_rot = 0.;
	cam->z_rot = 0.;
	compute_pos(cam);
}

void	compute_pos(t_cam *cam)
{
	t_quat	res;
	t_quat	conj_res;
	t_quat	x;
	t_quat	y;
	t_quat	z;

	cam->dir = (t_v3){0., 1., 0.};
	cam->right = (t_v3){1., 0., 0.};
	cam->up = (t_v3){0., 0., 1.};
	spheric_to_cart(&cam->pos, cam->r, cam->theta, cam->phi);
	x = q_local_rot(cam->right, cam->x_rot);
	y = q_local_rot(cam->dir, cam->y_rot);
	z = q_local_rot(cam->up, cam->z_rot);
	res = q_mult(q_mult(z, y), x);
	conj_res = q_conj(res);
	cam->dir = q_to_v3(q_mult(q_mult(res, v3_to_q(cam->dir)), conj_res));
	cam->right = q_to_v3(q_mult(q_mult(res, v3_to_q(cam->right)), conj_res));
	cam->up = q_to_v3(q_mult(q_mult(res, v3_to_q(cam->up)), conj_res));
}
