/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 00:27:57 by wta               #+#    #+#             */
/*   Updated: 2019/02/12 11:19:15 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"
#include "rtv1.h"

t_v3	normal_plane(t_ray *ray, t_v3 *hit, t_obj *obj)
{
	t_v3	normal;

	if (v3dot(ray->dir, obj->n) < 0)
	{
		obj->n = v3multf(obj->n, -1);
		*hit = v3add(*hit, v3multf(obj->n, EPS));
	}
	else
		*hit = v3add(*hit, v3multf(obj->n, -EPS));
	normal = obj->n;
	return (v3normalize(normal));
}

t_v3	normal_sphere(t_ray *ray, t_v3 *hit, t_obj *obj)
{
	t_v3	normal;
	t_v3	tmp;

	tmp = v3sub(*hit, obj->pos);
	normal = v3normalize(tmp);
	if (v3dot(ray->dir, tmp) >= 0)
	{
		normal = v3multf(normal, -1);
		*hit = v3add(*hit, v3multf(normal, -EPS));
	}
	else
		*hit = v3add(*hit, v3multf(normal, EPS));
	return (normal);
}

t_v3	normal_cylinder(t_ray *ray, t_v3 *hit, t_obj *obj)
{
	t_v3	normal;
	t_v3	tmp;
	t_v3	tmp2;

	tmp = v3sub(*hit, obj->pos);
	tmp2 = v3sub(ray->pos, obj->pos);
	tmp = v3sub(tmp, v3project(tmp, obj->dir));
	tmp2 = v3sub(tmp2, v3project(tmp2, obj->dir));
	normal = v3normalize(tmp);
	if (v3norm(tmp2) < v3norm(tmp))
		*hit = v3add(*hit, v3multf(normal, -EPS));
	else
		*hit = v3add(*hit, v3multf(normal, EPS));
	return (normal);
}

t_v3	normal_cone(t_ray *ray, t_v3 *hit, t_obj *obj)
{
	t_v3	normal;
	t_v3	tmp;
	t_v3	tmp2;

	tmp = v3sub(*hit, obj->pos);
	if (v3dot(tmp, obj->dir) < 0)
		tmp2 = v3cross(tmp, obj->dir);
	else
		tmp2 = v3cross(obj->dir, tmp);
	normal = v3normalize(v3cross(tmp2, tmp));
	if (v3dot(ray->dir, normal) > 0)
		*hit = v3add(*hit, v3multf(normal, -EPS));
	return (normal);
}

t_v3	get_normal(t_ray *ray, t_v3 *hit, t_obj *obj)
{
	t_v3	normal;

	normal = (t_v3){0., 0., 1.};
	if (obj->type == PLANE)
		normal = normal_plane(ray, hit, obj);
	if (obj->type == SPHERE)
		normal = normal_sphere(ray, hit, obj);
	if (obj->type == CYLINDER)
		normal = normal_cylinder(ray, hit, obj);
	if (obj->type == CONE)
		normal = normal_cone(ray, hit, obj);
	return (normal);
}
