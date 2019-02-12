/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 00:45:30 by wta               #+#    #+#             */
/*   Updated: 2019/02/12 00:45:32 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

t_obj	new_light(char type, t_v3 pos, t_v3 color, t_v3 aux)
{
	t_obj	new;

	new.type = type;
	new.radius = aux.x;
	new.i = aux.y;
	new.pos = pos;
	new.color = color;
	return (new);
}

t_obj	new_sphere(t_v3 pos, t_v3 color, double radius, t_q phong)
{
	t_obj	new;

	new.type = SPHERE;
	new.radius = radius;
	new.pos = pos;
	new.color = color;
	new.phong = phong;
	return (new);
}

t_obj	new_plane(t_v3 pos, t_v3 n, t_v3 color, t_q phong)
{
	t_obj	new;

	new.type = PLANE;
	new.radius = 0.;
	new.pos = pos;
	new.n = n;
	new.color = color;
	new.phong = phong;
	return (new);
}

t_obj	new_cylinder(t_v3 pos, t_v3 dir, t_v3 color, t_q phong)
{
	t_obj	new;

	new.type = CYLINDER;
	new.radius = 2;
	new.pos = pos;
	new.dir = v3normalize(dir);
	new.color = color;
	new.phong = phong;
	return (new);
}

t_obj	new_cone(t_v3 pos, t_v3 dir, t_v3 color, t_q phong)
{
	t_obj	new;

	new.type = CONE;
	new.angle = M_PI / 20;
	new.pos = pos;
	new.dir = v3normalize(dir);
	new.color = color;
	new.phong = phong;
	return (new);
}
