/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadratic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 18:09:29 by wta               #+#    #+#             */
/*   Updated: 2019/02/11 01:46:51 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vectors.h"
#include "rtv1.h"
#include <stdio.h>
double		do_quad(t_quad quad)
{
	quad.det = sqr(quad.b) - 4 * quad.a * quad.c;
	if (quad.det > 0.)
	{
		quad.r0 = (-quad.b + sqrt(quad.det)) / (2 * quad.a);
		quad.r1 = (-quad.b - sqrt(quad.det)) / (2 * quad.a);
		if (quad.r0 < 0 && quad.r1 >= 0)
			return (quad.r1);
		if (quad.r1 < 0 && quad.r0 >= 0)
			return (quad.r0);
		return ((quad.r0 < quad.r1) ? quad.r0 : quad.r1);
	}
	return ((quad.det == 0) ? -quad.b / (2 * quad.a) : -1);
}
