/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 00:33:02 by wta               #+#    #+#             */
/*   Updated: 2019/01/22 03:40:23 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vectors.h"
#include "rtv1.h"

void		pxl_to_img(t_img *img, int x, int y, int color)
{
	img->img_str[x + (y * img->sizel / 4)] = color;
}

/*
 *	Les 0. sont les coordonnees du centre de la sphere
 */

#include <stdio.h>

double	intersect_sphere(t_cam *cam)
{
	t_vec3	var;
	t_vec3	det;
	t_vec3	sphere;
	double	radius;

	sphere = (t_vec3){0., 0., 0.};
	radius = 1.;
	var.x = cam->ray.x * cam->ray.x + cam->ray.y * cam->ray.y
		+ cam->ray.z * cam->ray.z;
	var.y =	2 * ((cam->ray.x * (cam->pos.x - sphere.x) + cam->ray.y
		* (cam->pos.y - sphere.y) + cam->ray.z * (cam->pos.z - sphere.z)));
	var.z = ((cam->pos.x - sphere.x) * (cam->pos.x - sphere.x) + (cam->pos.y - sphere.y)
		* (cam->pos.y - sphere.y) + (cam->pos.z - sphere.z) * (cam->pos.z - sphere.z)) - radius * radius;
	det.x = var.y * var.y - 4 * var.x * var.z;
	if (det.x > 0.)
	{
		det.y = (-var.y + sqrt(det.x)) / (2 * var.x);
		det.z = (-var.y - sqrt(det.x)) / (2 * var.x);
		if (det.y > det.z)
			return (det.y);
		return (det.z);
	}
	if (det.x == 0.)
		return (-var.y / (2 * var.x));
	return (-1.);
}

double	intersect_plane(t_cam *cam)
{
	t_vec3	normal;
	double	denom;
	double	dist;

	normal = (t_vec3){0., 1., 0.};
	denom = vec3_dot(normal, cam->ray);
	if (fabs(denom) > 0.001f)
	{
		dist = vec3_dot(vec3_sub((t_vec3){0., 0., 0.}, cam->pos), normal) / denom;
		return (dist >= 0);
	}
	return (-1);
}

int	cast_ray(t_vec3	*pos, t_cam *cam)
{
	cam->ray = vec3_normalize(vec3_sub(*pos, cam->pos));
	if (intersect_sphere(cam) > -1.)
		return (0xffffff);
//	if (intersect_plane(cam) != -1.)
//		return (0xff0000);
	return (0x0);
}

void	render(t_img *img, t_cam *cam, t_view *view)
{
	t_vec3	pxl_pos;
	t_vec3	view_pos;
	t_vec3	indent;
	int		color;

	indent = (t_vec3){view->width / SCREEN_W, view->height / SCREEN_H, 0.};
	view_pos = (t_vec3){-view->width / 2.,
		-view->height / 2., -9.};
	pxl_pos.y = -1;
	while (++pxl_pos.y < SCREEN_H)
	{
		pxl_pos.x = -1;
		while (++pxl_pos.x < SCREEN_W)
		{
			color = cast_ray(&view_pos, cam);
			pxl_to_img(img, pxl_pos.x, pxl_pos.y, color);
			view_pos.x += indent.x;
		}
		view_pos.x = -view->width / 2.;
		view_pos.y += indent.y;
	}
}
