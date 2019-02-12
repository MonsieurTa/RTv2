/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 00:22:53 by wta               #+#    #+#             */
/*   Updated: 2019/02/12 00:23:25 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_v3	multf_color(t_v3 color, double coef)
{
	t_v3	new;

	new.x = clampf(color.x * coef, 255., 0.);
	new.y = clampf(color.y * coef, 255., 0.);
	new.z = clampf(color.z * coef, 255., 0.);
	return (new);
}

t_v3	add_color(t_v3 c1, t_v3 c2)
{
	t_v3	new;

	new.x = clampf(c1.x + c2.x, 255., 0.);
	new.y = clampf(c1.y + c2.y, 255., 0.);
	new.z = clampf(c1.z + c2.z, 255., 0.);
	return (new);
}
