/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 18:35:12 by wta               #+#    #+#             */
/*   Updated: 2019/02/11 05:08:02 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "rtv1.h"

void	pxl_to_img(t_img *img, int x, int y, int color)
{
	img->img_str[x + (y * SCREEN_W)] = color;
}

double	intersect_plane(t_ray *ray, t_obj *plane)
{
	double	denom;
	double	t;
	t_v3	pos;

	denom = v3dot(plane->n, ray->dir);
	if ((denom = v3dot(plane->n, ray->dir)) != 0.)
	{
		pos = v3sub(plane->pos, ray->pos);
		t = v3dot(pos, plane->n) / denom;
		return ((t >= 0.) ? t : -1);
	}
	return (-1);
}

double	intersect_sphere(t_ray *ray, t_obj *sphere)
{
	t_v3	moveto;
	t_quad	quad;

	moveto = v3sub(ray->pos, sphere->pos);
	quad.a = v3dot(ray->dir, ray->dir);
	quad.b = 2 * v3dot(ray->dir, moveto);
	quad.c = v3dot(moveto, moveto) - sqr(sphere->radius);
	return (do_quad(quad));
}

double	intersect_cylinder(t_ray *ray, t_obj *cylinder)
{
	t_ray	c;
	t_ray	raycpy;
	t_obj	sphere;

	c.pos = v3project(cylinder->pos, cylinder->dir);
	c.dir = v3sub(cylinder->pos, c.pos);
	raycpy.pos = v3project(ray->pos, cylinder->dir);
	raycpy.pos = v3sub(ray->pos, raycpy.pos);
	raycpy.dir = v3project(ray->dir, cylinder->dir);
	raycpy.dir = v3sub(ray->dir, raycpy.dir);
	sphere.pos = c.dir;
	sphere.color = cylinder->color;
	sphere.radius = cylinder->radius;
	sphere.phong = cylinder->phong;
	return (intersect_sphere(&raycpy, &sphere));
}

double	intersect_cone(t_ray *ray, t_obj *cone)
{
	t_v3	moveto;
	t_quad	quad;

	moveto = v3sub(ray->pos, cone->pos);
	quad.a = sqr(v3dot(ray->dir, cone->dir)) - sqr(cos(cone->angle));
	quad.b = 2 * (v3dot(ray->dir, cone->dir) * v3dot(moveto, cone->dir) - v3dot(ray->dir, moveto)
				* sqr(cos(cone->angle)));
	quad.c = sqr(v3dot(moveto, cone->dir)) - v3dot(moveto, moveto) * sqr(cos(cone->angle));
	return (do_quad(quad));
}

int		clamp(double value, int max, int min)
{
	if ((int)value > max)
		return (max);
	if ((int)value < min)
		return (min);
	return ((int)value);
}

int		clampf(double value, double max, double min)
{
	if (value > max)
		return (max);
	if (value < min)
		return (min);
	return (value);
}

int		v3toi(t_v3 v)
{
	int		color;
	t_uchar	*ptr;

	ptr = (t_uchar*)&color;
	ptr[0] = clamp(v.x, 255, 0);
	ptr[1] = clamp(v.y, 255, 0);
	ptr[2] = clamp(v.z, 255, 0);
	return (color);
}

t_v3	multf_color(t_v3 color, double coef)
{
	t_v3	new;

	new.x = clampf(color.x * coef, 255., 0.);
	new.y = clampf(color.y * coef, 255., 0.);
	new.z = clampf(color.z * coef, 255., 0.);
	return (new);
}

t_v3	add_color(t_v3 c1, t_v3 c2)
{
	t_v3	new;

	new.x = clampf(c1.x + c2.x, 255., 0.);
	new.y = clampf(c1.y + c2.y, 255., 0.);
	new.z = clampf(c1.z + c2.z, 255., 0.);
	return (new);
}

int		cast_shadow(t_v3 *l_dir, t_v3 *hit, t_lst *obj)
{
	t_node 	*node;
	t_ray	shadow;
	double	dist = v3norm(*l_dir);
	double	t;

	node = obj->head;
	shadow = (t_ray){*hit, v3normalize(v3multf(*l_dir, -1))};
	while (node != NULL)
	{
		if (node->obj.type == SPHERE &&
				((t = intersect_sphere(&shadow, &node->obj)) >= 0.0001 && t < dist))
			return (1);
		if (node->obj.type == PLANE &&
				((t = intersect_plane(&shadow, &node->obj)) >= 0.0001 && t < dist))
			return (1);
		if (node->obj.type == CYLINDER &&
				((t = intersect_cylinder(&shadow, &node->obj)) >= 0.0001 && t < dist))
			return (1);
		if (node->obj.type == CONE &&
				((t = intersect_cone(&shadow, &node->obj)) >= 0.0001 && t < dist))
			return (1);
		node = node->next;
	}
	return (0);
}

t_v3	get_normal(t_env *env, t_v3 *hit, t_obj *obj)
{
	t_v3	normal;
	t_v3	tmp;
	t_v3	tmp2;

	if (obj->type == PLANE)
	{
		if (v3dot(env->ray.dir, obj->n) >= 0)
			normal = v3multf(obj->n, -1);
		else
			normal = obj->n;
	}
	if (obj->type == SPHERE)
	{
		tmp = v3sub(*hit, obj->pos);
		*hit = v3add(*hit, v3multf(tmp, 0.0001));
		if (v3dot(env->ray.dir, tmp) >= 0)
			normal = v3normalize(v3multf(tmp, -1));
		else
			normal = v3normalize(tmp);
	}
	if (obj->type == CYLINDER)
	{
		tmp = v3sub(*hit, obj->pos);
		tmp2 = v3sub(env->ray.pos, obj->pos);
		tmp = v3sub(tmp, v3project(tmp, obj->dir));
		tmp2 = v3sub(tmp2, v3project(tmp2, obj->dir));
		normal = v3normalize(tmp);
		if (v3norm(tmp2) < v3norm(tmp))
			*hit = v3add(*hit, v3multf(normal, -0.0001));
		else
			*hit = v3add(*hit, v3multf(normal, 0.0001));
	}
	if (obj->type == CONE)
	{
		tmp = v3sub(*hit, obj->pos);
		if (v3dot(tmp, obj->dir) < 0)
			tmp2 = v3cross(tmp, obj->dir);
		else
			tmp2 = v3cross(obj->dir, tmp);
		normal = v3normalize(v3cross(tmp2, tmp));
		if (v3dot(env->ray.dir, normal) > 0)
			*hit = v3add(*hit, v3multf(normal, -0.0001));
	}
	return (normal);
}

t_v3	compute_lights(t_env *env, t_obj *obj)
{
	t_node	*node;
	t_v3	l_dir;
	t_v3	color;
	t_v3	n;
	double	dot;
	double	i;

	node = env->lights.head;
	color = (t_v3){0., 0., 0.};
	while (node != NULL)
	{
		i = node->obj.i;
		if (node->obj.type == AMBT_LIGHT)
			color = multf_color(obj->color, i);
		else
		{
			t_v3 hit = v3add(env->ray.pos, v3multf(env->ray.dir, env->t));
			n = get_normal(env, &hit, obj);
			l_dir = v3sub(hit, node->obj.pos);
			if (cast_shadow(&l_dir, &hit, &env->objs) != 1)
			{
				l_dir = v3normalize(l_dir);
				dot = -v3dot(n, l_dir);
				if (dot > 0.)
				{
					color = add_color(color, multf_color(obj->color, i * dot / v3norm(n) * v3norm(l_dir)));
					color = add_color(color, multf_color(node->obj.color, i * pow(dot, 50)));
				}
			}
		}
		node = node->next;
	}
	return (color);
}

int		cast_ray(t_env *env, t_obj *obj)
{
	if ((obj->type == PLANE && (env->t = intersect_plane(&env->ray, obj)) >= 0.
				&& env->t < env->tmax)
			|| (obj->type == SPHERE && (env->t = intersect_sphere(&env->ray, obj)) >= 0.
				&& env->t < env->tmax)
			|| (obj->type == CYLINDER && (env->t = intersect_cylinder(&env->ray, obj)) >= 0. && env->t < env->tmax)
			|| (obj->type == CONE && (env->t = intersect_cone(&env->ray, obj)) >= 0. && env->t < env->tmax))
	{
		env->pxl_clr = v3toi(compute_lights(env, obj));
		env->tmax = env->t;
		return (1);
	}
	return (0);
}

void	raycasting(t_env *env, int x, int y)
{
	t_node	*node;
	int		res;

	node = env->objs.head;
	env->tmax = INFINITY;
	res = 0;
	while (x % env->pxl == 0 && node != NULL)
	{
		if (cast_ray(env, &node->obj) == 1)
			res = 1;
		node = node->next;
	}
	if (res == 0 && x % env->pxl == 0)
		env->pxl_clr = 0x282828;
	pxl_to_img(&env->mlx.img, x, y, env->pxl_clr);
}

void	render(t_env *env)
{
	t_v3	pxl;
	t_v3	tmp;
	t_v3	inc;

	pxl.y = -1;
	inc.y = 0. - env->cam.view.i.y;
	while ((inc.y += env->cam.view.i.y) < env->cam.view.height)
	{
		++pxl.y;
		pxl.x = -1;
		inc.x = 0. - env->cam.view.i.x;
		while ((inc.x += env->cam.view.i.x) < env->cam.view.width)
		{
			++pxl.x;
			tmp = v3sub(v3multf(env->cam.right, inc.x), v3multf(env->cam.up, inc.y));
			tmp = v3add(env->cam.view.origin, tmp);
			env->ray.dir = v3normalize(v3sub(tmp, env->cam.pos));
			env->ray.pos = env->cam.pos;
			raycasting(env, (int)pxl.x, (int)pxl.y);
		}
	}
}
