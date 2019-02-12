/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 00:23:43 by wta               #+#    #+#             */
/*   Updated: 2019/02/12 11:20:33 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vectors.h"
#include "rtv1.h"

double	intersect_plane(t_ray *ray, t_obj *plane)
{
	double	denom;
	double	t;
	t_v3	pos;

	denom = v3dot(plane->n, ray->dir);
	if ((denom = v3dot(plane->n, ray->dir)) > 0.)
	{
		pos = v3sub(plane->pos, ray->pos);
		t = v3dot(pos, plane->n) / denom;
		return ((t >= EPS) ? t : -1);
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
	quad.b = 2 * (v3dot(ray->dir, cone->dir) * v3dot(moveto, cone->dir)
		- v3dot(ray->dir, moveto)
			* sqr(cos(cone->angle)));
	quad.c = sqr(v3dot(moveto, cone->dir)) - v3dot(moveto, moveto)
		* sqr(cos(cone->angle));
	return (do_quad(quad));
}
