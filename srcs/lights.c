/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 00:46:35 by wta               #+#    #+#             */
/*   Updated: 2019/03/27 22:28:54 by williamta        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "vectors.h"
#include "rtv1.h"

int		cast_shadow(t_ray *light, t_v3 *hit, t_lst *obj)
{
	t_node		*node;
	t_ray		shadow;
	double		d;
	double		t;

	node = obj->head;
	shadow = (t_ray){*hit, v3normalize(v3multf(light->dir, -1)), 0., 0.};
	d = v3norm(light->dir);
	while (node != NULL)
	{
		t_v3	tmp = v3sub(light->pos, node->obj.pos);
		if ((node->obj.type == PLANE && v3dot(&tmp, &node->obj.n) == 0)
				|| (node->obj.type == SPHERE && ((t = intersect_sphere(&shadow,
								&node->obj)) >= EPS && t < d))
				|| (node->obj.type == PLANE && ((t = intersect_plane(&shadow,
								&node->obj)) >= EPS && t < d))
				|| (node->obj.type == CYLINDER
					&& ((t = intersect_cylinder(&shadow, &node->obj)) >= EPS
						&& t < d))
				|| (node->obj.type == CONE && ((t = intersect_cone(&shadow,
								&node->obj)) >= EPS && t < d)))
			return (1);
		node = node->next;
	}
	return (0);
}



void	do_shading(t_ray *ray, t_obj *obj, t_node *node, t_shading *shading)
{
	double	dot;
	double	tmp;
	double	t;
	t_v3	vtmp;

	t = v3norm(v3sub(node->obj.pos, shading->hit));
	shading->light.dir = v3normalize(shading->light.dir);
	dot = -v3dot(&shading->normal, &shading->light.dir);
	if (dot > 0.)
	{
		tmp = shading->i * dot / t;
		shading->color = add_color(shading->color, multf_color(obj->color,
					tmp));
		shading->color = add_color(shading->color, multf_color(node->obj.color,
					tmp));
		if (obj->specular > EPS)
		{
			tmp = -2 * dot;
			vtmp = v3sub(v3multf(shading->normal, tmp), shading->light.dir);
			if ((tmp = v3dot(&ray->dir, &vtmp)) > 0)
				shading->color = add_color(shading->color
						, v3multf(multf_color(node->obj.color
							, pow(tmp, obj->specular)), shading->i / t));
		}
	}
}

void	compute_lights(t_env *env, t_ray *ray, t_shading *shading, t_obj *obj)
{
	t_node	*node;

	node = env->lights.head;
	while (node != NULL)
	{
		shading->i = node->obj.i;
		if (node->obj.type == AMBT_LIGHT)
			shading->color = multf_color(obj->color, shading->i);
		else
		{
			shading->light = (t_ray){node->obj.pos,
				v3sub(shading->hit, node->obj.pos), 0, 0};
			if (env->shadow == 0 && cast_shadow(&shading->light
						, &shading->hit, &env->objs) == 0)
				do_shading(ray, obj, node, shading);
			else if (env->shadow == 1)
				do_shading(ray, obj, node, shading);
		}
		node = node->next;
	}
}
