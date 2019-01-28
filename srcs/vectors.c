/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:13:17 by wta               #+#    #+#             */
/*   Updated: 2019/01/25 12:43:21 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_v3	v3add(t_v3 v, t_v3 w)
{
	t_v3	vector;

	vector = (t_v3){v.x + w.x, v.y + w.y, v.z + w.z};
	return (vector);
}

t_v3	v3sub(t_v3 v, t_v3 w)
{
	t_v3	vector;

	vector = (t_v3){v.x - w.x, v.y - w.y, v.z - w.z};
	return (vector);
}

t_v3	v3mult(t_v3 v, t_v3 w)
{
	t_v3	vector;

	vector = (t_v3){v.x * w.x, v.y * w.y, v.z * w.z};
	return (vector);
}

t_v3	v3multf(t_v3 v, double scalar)
{
	t_v3	vector;

	vector = (t_v3){v.x * scalar, v.y * scalar, v.z * scalar};
	return (vector);
}

t_v3	v3cross(t_v3 v, t_v3 w)
{
	t_v3	vector;

	vector = (t_v3){v.y * w.z - v.z * w.y,
		v.z * w.x - v.x * w.z,
		v.x * w.y - v.y * w.x};
	return (vector);
}
