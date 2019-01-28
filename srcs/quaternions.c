/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:18:19 by wta               #+#    #+#             */
/*   Updated: 2019/01/27 20:12:40 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "quaternions.h"

t_quat	q_normalize(t_quat quat)
{
	t_quat	normalized;
	double	magnitude;

	normalized = quat;
	magnitude = sqr(quat.w) + sqr(quat.x) + sqr(quat.y) + sqr(quat.z);
	if (magnitude != 1.0)
	{
		magnitude = sqrt(magnitude);
		normalized.w /= magnitude;
		normalized.x /= magnitude;
		normalized.y /= magnitude;
		normalized.z /= magnitude;
	}
	return (normalized);
}

t_quat	q_mult(t_quat q1, t_quat q2)
{
	t_quat	new;

	new.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	new.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	new.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	new.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	return (new);
}

t_quat	q_local_rot(t_v3 axis, double angle)
{
	t_quat	new;

	new.w = cos(angle / 2);
	new.x = axis.x * sin(angle / 2);
	new.y = axis.y * sin(angle / 2);
	new.z = axis.z * sin(angle / 2);
	return (new);
}

t_quat	q_conj(t_quat q)
{
	t_quat	new;

	new.w = q.w;
	new.x = -q.x;
	new.y = -q.y;
	new.z = -q.z;
	return (new);
}

t_quat	v3_to_q(t_v3 v)
{
	t_quat	q;

	q.w = 0.;
	q.x = v.x;
	q.y = v.y;
	q.z = v.z;
	return (q);
}

t_v3	q_to_v3(t_quat q)
{
	t_v3	v;

	v.x = q.x;
	v.y = q.y;
	v.z = q.z;
	return (v);
}
