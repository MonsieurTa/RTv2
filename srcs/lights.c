/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 17:30:18 by wta               #+#    #+#             */
/*   Updated: 2019/01/29 17:24:19 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
