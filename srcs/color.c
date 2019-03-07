/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 00:22:53 by wta               #+#    #+#             */
/*   Updated: 2019/03/07 02:56:34 by wta              ###   ########.fr       */
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

	new.x = (1 - (1 - c1.x / 255) * (1 - c2.x / 255)) * 255;
	new.y = (1 - (1 - c1.y / 255) * (1 - c2.y / 255)) * 255;
	new.z = (1 - (1 - c1.z / 255) * (1 - c2.z / 255)) * 255;
	return (new);
}
