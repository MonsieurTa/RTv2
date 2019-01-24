/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 00:33:02 by wta               #+#    #+#             */
/*   Updated: 2019/01/24 03:51:51 by wta              ###   ########.fr       */
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

double	intersect_sphere(t_ray *ray, t_obj sphere)
{
	t_vec3	moveto;
	t_quad	quad;

	ray->dir = vec3_normalize(ray->dir);
	moveto = vec3_sub(ray->pos, sphere.pos);
	quad.a = vec3_dot(ray->dir, ray->dir);
	quad.b = 2 * vec3_dot(ray->dir, moveto);
	quad.c = vec3_dot(moveto, moveto) - (sphere.radius * sphere.radius);
	return (do_quad(quad));
}

double	intersect_plane(t_ray *ray, t_obj plane)
{
	t_vec3	moveto;
	double	denom;
	double	dist;

	ray->dir = vec3_normalize(ray->dir);
	moveto = vec3_sub(ray->pos, plane.normal);
	denom = vec3_dot(ray->dir, plane.normal);
	if (denom > 0.001)
	{
		dist = -vec3_dot(moveto, plane.normal) / denom;
		return (dist >= 0. ? dist : -1);
	}
	return (-1);
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

int		cast_shadow(t_vec3 *l_dir, t_vec3 *hit, t_lst *obj)
{
	t_ray	shadow;

	obj->node = obj->head;
	shadow = (t_ray){*hit, *l_dir};
	while (obj->node != NULL)
	{
		if (obj->node->obj.type == SPHERE &&
			intersect_sphere(&shadow, obj->node->obj) >= 0.)
			return (1);
		if (obj->node->obj.type == PLANE &&
			intersect_plane(&shadow, obj->node->obj) >= 0.)
			return (1);
		obj->node = obj->node->next;
	}
	return (0);
}

double	compute_lights(t_scene *scene, t_lst *lights, t_obj *obj)
{
	t_vec3	l_dir;
	double	dot;
	double	i;

	i = 0.;
	lights->node = lights->head;
	while (lights->node != NULL)
	{
		if (lights->node->obj.type == DST_LIGHT)
			i += lights->node->obj.intensity;
		else
		{
			scene->mat.hit = vec3_add(scene->cam.pos, vec3_multf(scene->cam.ray.dir, scene->mat.t));
			scene->mat.n = vec3_normalize(vec3_sub(scene->mat.hit, obj->pos));
			l_dir = vec3_normalize(vec3_sub(lights->node->obj.pos, scene->mat.hit));
			if (cast_shadow(&l_dir, &scene->mat.hit, &scene->objs) != 1)
			{
				dot = vec3_dot(scene->mat.n, l_dir);
				if (dot > 0.)
					i += lights->node->obj.intensity * dot / vec3_norm(scene->mat.n)
						* vec3_norm(l_dir);
			}
		}
		lights->node = lights->node->next;
	}
	return (i > 1. ? 1. : i);
}

int	cast_ray(t_vec3	*pos, t_scene *scene, t_obj *obj)
{
	double		coef;

	scene->cam.ray.dir = vec3_normalize(vec3_sub(*pos, scene->cam.pos));
	scene->cam.ray.pos = scene->cam.pos;
	scene->mat.color = 0x282828;
	if ((obj->type == SPHERE
		&& (scene->mat.t = intersect_sphere(&scene->cam.ray, *obj)) >= 0.
		&& scene->mat.t < scene->mat.tmax)
		|| (obj->type == PLANE
		&& (scene->mat.t = intersect_plane(&scene->cam.ray, *obj)) >= 0.
		&& scene->mat.t < scene->mat.tmax))
	{
		coef = compute_lights(scene, &scene->lights, obj);
		scene->mat.color = get_color(obj->color, coef);
		scene->mat.tmax = scene->mat.t;
	}
	return (scene->mat.t >= 0.);
}

void	raytracing(t_vec3 *pxl_pos, t_mlx *mlx, t_scene *scene)
{
	t_node	*node;

	scene->mat.tmax = 2000.;
	node = scene->objs.head;
	while (node != NULL)
	{
		if (cast_ray(&scene->view.pos, scene, &node->obj))
			pxl_to_img(&mlx->img, pxl_pos->x, pxl_pos->y, scene->mat.color);
		node = node->next;
	}
	if (scene->mat.tmax == 2000.)
		pxl_to_img(&mlx->img, pxl_pos->x, pxl_pos->y, scene->mat.color);
}

void	render(t_mlx *mlx, t_scene *scene)
{
	t_vec3	pxl_pos;
	t_vec3	indent;

	indent = (t_vec3){scene->view.width / SCREEN_W, scene->view.height / SCREEN_H, 0.};
	scene->view.pos = (t_vec3){-scene->view.width / 2. + indent.x / 2,
		scene->view.height / 2. - indent.y / 2, -9.};
	pxl_pos.y = -1;
	while (++pxl_pos.y < SCREEN_H)
	{
		pxl_pos.x = -1;
		while (++pxl_pos.x < SCREEN_W)
		{
			raytracing(&pxl_pos, mlx, scene);
			scene->view.pos.x += indent.x;
		}
		scene->view.pos.x = -scene->view.width / 2.;
		scene->view.pos.y -= indent.y;
	}
}
