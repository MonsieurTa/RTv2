/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 00:46:35 by wta               #+#    #+#             */
/*   Updated: 2019/02/26 17:55:52 by wta              ###   ########.fr       */
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
		if ((node->obj.type == PLANE && v3dot(v3sub(light->pos, node->obj.pos),
					node->obj.n) == 0)
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

void	do_shading(t_obj *obj, t_node *node, t_shading *shading)
{
	double	dot;

	shading->light.dir = v3normalize(shading->light.dir);
	dot = -v3dot(shading->normal, shading->light.dir);
	if (dot > 0.)
	{
		shading->color = add_color(shading->color, multf_color(obj->color,
					shading->i * dot / v3norm(shading->normal)
					* v3norm(shading->light.dir)));
		if (obj->phong.w > EPS)
			shading->color = add_color(shading->color
					, multf_color(node->obj.color
						, shading->i * pow(dot, obj->phong.w)));
	}
}

void	compute_lights(t_env *env, t_shading *shading, t_obj *obj)
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
			if (cast_shadow(&shading->light, &shading->hit, &env->objs) == 0)
				do_shading(obj, node, shading);
		}
		node = node->next;
	}
}
