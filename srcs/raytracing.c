/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 18:35:12 by wta               #+#    #+#             */
/*   Updated: 2019/01/28 23:05:34 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <stdio.h>

void	pxl_to_img(t_img *img, int x, int y, int color)
{
	img->img_str[x + (y * img->sizel / 4)] = color;
}

int		intersect_plane(t_env *env, t_obj *plane)
{
	double	denom;
	double	t;
	t_v3	pos;

	if ((denom = v3dot(plane->n, env->ray.dir)) != 0.)
	{
		pos = v3sub(plane->pos, env->ray.pos);
		t = v3dot(pos, plane->n) / denom;
		return ((t >= 0.0001) ? t : -1);
	}
	return (-1);
}

double	intersect_sphere(t_env *env, t_obj *sphere)
{
	t_v3	moveto;
	t_quad	quad;

	env->ray.dir = v3normalize(env->ray.dir);
	moveto = v3sub(env->ray.pos, sphere->pos);
	quad.a = v3dot(env->ray.dir, env->ray.dir);
	quad.b = 2 * v3dot(env->ray.dir, moveto);
	quad.c = v3dot(moveto, moveto) - sqr(sphere->radius);
	return (do_quad(quad));
}


int		cast_ray(t_env *env, t_obj *obj)
{
	if (obj->type == PLANE && (env->t = intersect_plane(env, obj)) >= 0.
			&& env->t < env->tmax)
	{
		env->tmax = env->t;
		return (1);
	}
//	if (obj->type == SPHERE && (env->t = intersect_sphere(env, obj)) >= 0.
//			&& env->t < env->tmax)
//	{
//		env->tmax = env->t;
//		return (1);
//	}
	return (0);
}

void	raycasting(t_env *env, int x, int y)
{
	t_node	*node;

	node = env->objs.head;
	env->tmax = 2000.;
	while (node != NULL)
	{
		if (cast_ray(env, &node->obj) == 1)
			pxl_to_img(&env->mlx.img, x, y, 0xffffff);
		else
			pxl_to_img(&env->mlx.img, x, y, 0x282828);
		node = node->next;
	}
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
			tmp = v3add(v3multf(env->cam.right, inc.x), v3multf(env->cam.up, -inc.y));
			tmp = v3add(env->cam.view.origin, tmp);
			env->ray.dir = v3normalize(v3sub(tmp, env->cam.pos));
			env->ray.pos = env->cam.pos;
			raycasting(env, (int)pxl.x, (int)pxl.y);
		}
	}
}
