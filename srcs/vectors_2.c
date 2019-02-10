/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:44:28 by wta               #+#    #+#             */
/*   Updated: 2019/02/10 04:43:17 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vectors.h"

double	v3dot(t_v3 v, t_v3 w)
{
	return (v.x * w.x + v.y * w.y + v.z * w.z);
}

double	v3norm(t_v3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	v3normf(t_v3 v, double scalar)
{
	return (scalar * v3norm(v));
}

double	v3cos(t_v3 v, t_v3 w)
{
	return (v3dot(v, w) / (v3norm(v) * v3norm(w)));
}

t_v3	v3normalize(t_v3 v)
{
	double	length;
	t_v3	vector;

	length = v3norm(v);
	vector = (t_v3){v.x / length, v.y / length, v.z / length};
	return (vector);
}

t_v3	v3project(t_v3 v, t_v3 w)
{
	t_v3	vector;
	double	scalar;

	scalar = v3dot(v, w) / v3dot(w, w);
	vector = v3multf(w, scalar);
	return (vector);
}
