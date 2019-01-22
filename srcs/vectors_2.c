/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:44:28 by wta               #+#    #+#             */
/*   Updated: 2019/01/21 20:49:31 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vectors.h"

double	vec3_dot(t_vec3 v, t_vec3 w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

double	vec3_norm(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	vec3_normf(t_vec3 v, double scalar)
{
	return (scalar * vec3_norm(v));
}

double	vec3_cos(t_vec3 v, t_vec3 w)
{
	return (vec3_dot(v, w) / (vec3_norm(v) * vec3_norm(w)));
}

t_vec3	vec3_normalize(t_vec3 v)
{
	double	length;
	t_vec3	vector;

	length = vec3_norm(v);
	vector = (t_vec3){v.x / length, v.y / length, v.z / length};
	return (vector);
}
