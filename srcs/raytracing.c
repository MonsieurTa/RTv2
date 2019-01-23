/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 00:33:02 by wta               #+#    #+#             */
/*   Updated: 2019/01/23 17:39:40 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vectors.h"
#include "rtv1.h"

void		pxl_to_img(t_img *img, int x, int y, int color)
{
	img->img_str[x + (y * img->sizel / 4)] = color;
}

#include <stdio.h>

double	intersect_sphere(t_cam *cam, t_sphere sphere)
{
	t_vec3	moveto;
	t_quad	quad;

	cam->ray.dir = vec3_normalize(cam->ray.dir);
	moveto = vec3_sub(cam->ray.pos, sphere.pos);
	quad.a = vec3_dot(cam->ray.dir, cam->ray.dir);
	quad.b = 2 * vec3_dot(cam->ray.dir, moveto);
	quad.c = vec3_dot(moveto, moveto) - (sphere.radius * sphere.radius);
	return (do_quad(quad));
}

int	get_color(t_color color, double coef)
{
	int		final_color;
	t_uchar	*idx;

	final_color = 0;
	idx = (t_uchar*)&final_color;
	idx[0] = color.b * coef;
	idx[1] = color.g * coef;
	idx[2] = color.r * coef;
	return (final_color);
}

int	cast_ray(t_vec3	*pos, t_cam *cam)
{
	double		dist;
	double		angle;
	t_vec3		light = {-5., 0., -5.};
	t_vec3		light_dir;
	t_vec3		normal;
	t_vec3		hit;
	t_sphere	sphere = {{0.,3.,0.}, 1., {255, 0, 0}};
	int			color;

	cam->ray.dir = vec3_normalize(vec3_sub(*pos, cam->pos));
	cam->ray.pos = cam->pos;
	if ((dist = intersect_sphere(cam, sphere)) > -1.)
	{
		hit = vec3_add(cam->pos, vec3_multf(cam->ray.dir, dist));
		normal = vec3_normalize(vec3_sub(hit, sphere.pos));
		light_dir = vec3_normalize(vec3_sub(light, hit));
		angle = (vec3_dot(light_dir, normal)) / (vec3_norm(light_dir) * vec3_norm(normal));
		if (angle < 0.)
			return(0x0);
		//angle = acos(angle);
		color = get_color(sphere.color, 1 * vec3_dot(normal, light_dir));
		return (color);
	}
	return (0x282828);
}

void	render(t_img *img, t_cam *cam, t_view *view)
{
	t_vec3	pxl_pos;
	t_vec3	view_pos;
	t_vec3	indent;
	int		color;

	indent = (t_vec3){view->width / SCREEN_W, view->height / SCREEN_H, 0.};
	view_pos = (t_vec3){-view->width / 2. + indent.x / 2,
		view->height / 2. - indent.y / 2, -9.};
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
		view_pos.y -= indent.y;
	}
}
