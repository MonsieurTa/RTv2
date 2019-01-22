/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:13:17 by wta               #+#    #+#             */
/*   Updated: 2019/01/21 21:59:45 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_vec3	vec3_add(t_vec3 v, t_vec3 w)
{
	t_vec3	vector;

	vector = (t_vec3){v.x + w.x, v.y + w.y, v.z + w.z};
	return (vector);
}

t_vec3	vec3_sub(t_vec3 v, t_vec3 w)
{
	t_vec3	vector;

	vector = (t_vec3){v.x - w.x, v.y - w.y, v.z - w.z};
	return (vector);
}

t_vec3	vec3_mult(t_vec3 v, t_vec3 w)
{
	t_vec3	vector;

	vector = (t_vec3){v.x * w.x, v.y * w.y, v.z * w.z};
	return (vector);
}

t_vec3	vec3_multf(t_vec3 v, double scalar)
{
	t_vec3	vector;

	vector = (t_vec3){v.x * scalar, v.y * scalar, v.z * scalar};
	return (vector);
}

t_vec3	vec3_cross(t_vec3 v, t_vec3 w)
{
	t_vec3	vector;

	vector = (t_vec3){v.y * w.z - v.z * w.y,
		v.z * w.x - v.x * w.z,
		v.x * w.y - v.y * w.x};
	return (vector);
}
