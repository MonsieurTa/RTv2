/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 20:37:04 by wta               #+#    #+#             */
/*   Updated: 2019/01/24 01:01:19 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj	new_sphere(t_vec3 pos, double radius, t_color color)
{
	t_obj	sphere;

	sphere.type = SPHERE;
	sphere.pos = pos;
	sphere.radius = radius;
	sphere.color = color;
	return (sphere);
}

t_obj	new_plane(t_vec3 pos, t_color color)
{
	t_obj	plane;

	plane.type = PLANE;
	plane.color = color;
	return (plane);
}

t_obj	new_light(t_vec3 pos, double intensity, int type, t_color color)
{
	t_obj	light;

	light.type = type;
	light.pos = pos;
	light.intensity = intensity;
	light.color = color;
	return (light);
}
