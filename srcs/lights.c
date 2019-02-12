/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 00:46:35 by wta               #+#    #+#             */
/*   Updated: 2019/02/12 11:16:13 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "vectors.h"
#include "rtv1.h"

int		cast_shadow(t_v3 *l_dir, t_v3 *hit, t_lst *obj)
{
	t_node		*node;
	t_ray		shadow;
	double		d;
	double		t;

	node = obj->head;
	shadow = (t_ray){*hit, v3normalize(v3multf(*l_dir, -1)), 0., 0.};
	d = v3norm(*l_dir);
	while (node != NULL)
	{
		if (node->obj.type == SPHERE &&
				((t = intersect_sphere(&shadow, &node->obj)) >= EPS && t < d))
			return (1);
		if (node->obj.type == PLANE &&
				((t = intersect_plane(&shadow, &node->obj)) >= EPS && t < d))
			return (1);
		if (node->obj.type == CYLINDER &&
				((t = intersect_cylinder(&shadow, &node->obj)) >= EPS && t < d))
			return (1);
		if (node->obj.type == CONE &&
				((t = intersect_cone(&shadow, &node->obj)) >= EPS && t < d))
			return (1);
		node = node->next;
	}
	return (0);
}

void	do_shading(t_obj *obj, t_node *node, t_shading *shading)
{
	double	dot;

	shading->l_dir = v3normalize(shading->l_dir);
	dot = -v3dot(shading->normal, shading->l_dir);
	if (dot > 0.)
	{
		shading->color = add_color(shading->color, multf_color(obj->color,
					shading->i * dot / v3norm(shading->normal)
					* v3norm(shading->l_dir)));
		shading->color = add_color(shading->color, multf_color(node->obj.color,
					shading->i * pow(dot, 50)));
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
			shading->l_dir = v3sub(shading->hit, node->obj.pos);
			if (cast_shadow(&shading->l_dir, &shading->hit, &env->objs) == 0)
				do_shading(obj, node, shading);
		}
		node = node->next;
	}
}
