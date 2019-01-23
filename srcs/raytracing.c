/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 00:33:02 by wta               #+#    #+#             */
/*   Updated: 2019/01/23 23:07:14 by wta              ###   ########.fr       */
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

double	intersect_sphere(t_cam *cam, t_obj sphere)
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

double	compute_lights(t_cam *cam, t_lst *lights, t_obj *obj, t_mat *mat)
{
	t_vec3	hit;
	t_vec3	light_dir;
	double	dot;
	double	i;

	i = 0.;
	lights->node = lights->head;
	while (lights->node != NULL)
	{
		hit = vec3_add(cam->pos, vec3_multf(cam->ray.dir, mat->t));
		mat->normal = vec3_normalize(vec3_sub(hit, obj->pos));
		light_dir = vec3_normalize(vec3_sub(lights->node->obj.pos, hit));
		dot = vec3_dot(mat->normal, light_dir);
		if (dot > 0.)
			i += lights->node->obj.intensity * dot / vec3_norm(mat->normal) * vec3_norm(light_dir);
		lights->node = lights->node->next;
	}
	return (i);
}

int	cast_ray(t_vec3	*pos, t_scene *scene, t_obj *obj, t_mat *mat)
{
	double		coef;

	scene->cam.ray.dir = vec3_normalize(vec3_sub(*pos, scene->cam.pos));
	scene->cam.ray.pos = scene->cam.pos;
	mat->color = 0x282828;
	if ((mat->t = intersect_sphere(&scene->cam, *obj)) >= 0. && mat->t < mat->tmax)
	{
		coef = compute_lights(&scene->cam, &scene->lights, obj, mat);
		mat->color = get_color(obj->color, 1. * coef);
		mat->tmax = mat->t;
	}
	return (mat->t >= 0.);
}

void	raytracing(t_vec3 *pxl_pos, t_mlx *mlx, t_scene *scene)
{
	t_mat	mat;

	mat.tmax = 2000.;
	scene->objs.node = scene->objs.head;
	while (scene->objs.node != NULL)
	{
		if (cast_ray(&scene->view.pos, scene, &scene->objs.node->obj, &mat))
			pxl_to_img(&mlx->img, pxl_pos->x, pxl_pos->y, mat.color);
		scene->objs.node = scene->objs.node->next;
	}
	if (mat.tmax == 2000.)
		pxl_to_img(&mlx->img, pxl_pos->x, pxl_pos->y, mat.color);
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
