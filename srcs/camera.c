/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 12:52:13 by wta               #+#    #+#             */
/*   Updated: 2019/02/12 06:08:42 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vectors.h"
#include "rtv1.h"

void	set_view(t_view *view)
{
	double	tan_hangle;

	view->fov = M_PI / 2;
	tan_hangle = tan(view->fov / 2);
	view->width = tan_hangle * 2;
	view->height = SCREEN_H * (view->width / SCREEN_W);
	view->half_w = view->width / 2;
	view->half_h = view->height / 2;
	view->i.x = view->width / SCREEN_W;
	view->i.y = view->height / SCREEN_H;
	view->i.z = 0.;
}

void	init_cam(t_cam *cam)
{
	set_view(&cam->view);
	cam->pos.x = 0;
	cam->pos.y = 0;
	cam->pos.z = 0;
	cam->x_rot = 0.;
	cam->y_rot = 0.;
	cam->z_rot = 0.;
	compute_pos(cam);
}

t_v3	view_origin(t_cam *cam)
{
	t_v3	pos;
	t_v3	h_up;
	t_v3	h_left;
	t_v3	origin;

	h_up = v3multf(cam->up, cam->view.half_h - cam->view.i.y / 2);
	h_left = v3multf(cam->right, -cam->view.half_w + cam->view.i.x / 2);
	origin = v3add(cam->dir, v3add(h_up, h_left));
	pos = v3add(cam->pos, origin);
	return (pos);
}

void	compute_pos(t_cam *cam)
{
	t_q	res;
	t_q	conj_res;
	t_q	x;
	t_q	y;
	t_q	z;

	cam->dir = (t_v3){0., 1., 0.};
	cam->right = (t_v3){1., 0., 0.};
	cam->up = (t_v3){0., 0., 1.};
	x = q_local_rot(cam->right, cam->x_rot);
	y = q_local_rot(cam->dir, cam->y_rot);
	z = q_local_rot(cam->up, cam->z_rot);
	res = q_mult(q_mult(z, y), x);
	conj_res = q_conj(res);
	cam->dir = q_to_v3(q_mult(q_mult(res, v3_to_q(cam->dir)), conj_res));
	cam->right = q_to_v3(q_mult(q_mult(res, v3_to_q(cam->right)), conj_res));
	cam->up = q_to_v3(q_mult(q_mult(res, v3_to_q(cam->up)), conj_res));
	cam->view.origin = view_origin(cam);
}
