/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 01:51:28 by wta               #+#    #+#             */
/*   Updated: 2019/02/12 01:52:02 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "quaternions.h"

t_q	q_normalize(t_q q)
{
	t_q		normalized;
	double	magnitude;

	normalized = q;
	magnitude = sqr(q.w) + sqr(q.x) + sqr(q.y) + sqr(q.z);
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

t_q	q_mult(t_q q1, t_q q2)
{
	t_q	new;

	new.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	new.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	new.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	new.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	return (new);
}

t_q	q_local_rot(t_v3 axis, double angle)
{
	t_q	new;

	new.w = cos(angle / 2);
	new.x = axis.x * sin(angle / 2);
	new.y = axis.y * sin(angle / 2);
	new.z = axis.z * sin(angle / 2);
	return (new);
}

t_q	q_conj(t_q q)
{
	t_q	new;

	new.w = q.w;
	new.x = -q.x;
	new.y = -q.y;
	new.z = -q.z;
	return (new);
}

t_q	v3_to_q(t_v3 v)
{
	t_q	q;

	q.w = 0.;
	q.x = v.x;
	q.y = v.y;
	q.z = v.z;
	return (q);
}
