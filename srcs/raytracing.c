/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 18:35:12 by wta               #+#    #+#             */
/*   Updated: 2019/02/28 14:56:04 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../libft/includes/libft.h"
#include "rtv1.h"

int		cast_ray(t_env *env, t_ray *ray, t_obj *obj, int *color)
{
	t_shading	shading;
	double		t;

	ft_bzero(&shading, sizeof(t_shading));
	if ((obj->type == PLANE
			&& (t = intersect_plane(ray, obj)) >= 0.
				&& t < ray->tmax)
			|| (obj->type == SPHERE
				&& (t = intersect_sphere(ray, obj)) >= 0.
				&& t < ray->tmax)
			|| (obj->type == CYLINDER
				&& (t = intersect_cylinder(ray, obj)) >= 0.
				&& t < ray->tmax)
			|| (obj->type == CONE
				&& (t = intersect_cone(ray, obj)) >= 0.
				&& t < ray->tmax))
	{
		shading.hit = v3add(ray->pos, v3multf(ray->dir, t));
		shading.normal = get_normal(ray, &shading.hit, obj);
		compute_lights(env, ray, &shading, obj);
		*color = v3toi(shading.color);
		ray->tmax = t;
		return (1);
	}
	return (0);
}

void	raycasting(t_env *env, t_ray *ray, t_v3 *pxl)
{
	t_node	*node;
	int		res;

	node = env->objs.head;
	ray->tmax = 2000.;
	res = 0;
	while ((int)pxl->x % env->pxl == 0 && node != NULL)
	{
		if (cast_ray(env, ray, &node->obj, &ray->color) == 1)
			res = 1;
		node = node->next;
	}
	if (res == 0 && (int)pxl->x % env->pxl == 0)
		ray->color = 0x0;
	pxl_to_img(&env->mlx.img, (int)pxl->x, (int)pxl->y, ray->color);
}

void	init_render(t_env *env, double *max_h, t_v3 *inc, t_v3 *pxl)
{
	int		count;

	count = count_thread(&env->counter);
	*max_h = (count * env->spt + env->spt) * env->cam.view.height / SCREEN_H;
	pxl->x = -1;
	inc->y = ((count * env->spt * env->cam.view.height) / SCREEN_H)
		- env->cam.view.i.y;
	pxl->y = count * env->spt - 1;
}

void	render(t_env *env)
{
	t_ray	ray;
	t_v3	pxl;
	t_v3	tmp;
	t_v3	inc;
	double	max_h;

	init_render(env, &max_h, &inc, &pxl);
	while ((inc.y += env->cam.view.i.y) < max_h)
	{
		if (++pxl.y >= SCREEN_H)
			break ;
		pxl.x = -1;
		inc.x = 0 - env->cam.view.i.x;
		while ((inc.x += env->cam.view.i.x) < env->cam.view.width)
		{
			if (++pxl.x >= SCREEN_W)
				break ;
			tmp = v3sub(v3multf(env->cam.right, inc.x),
					v3multf(env->cam.up, inc.y));
			tmp = v3add(env->cam.view.origin, tmp);
			ray.dir = v3normalize(v3sub(tmp, env->cam.pos));
			ray.pos = env->cam.pos;
			raycasting(env, &ray, &pxl);
		}
	}
}
