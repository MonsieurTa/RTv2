/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:57:51 by wta               #+#    #+#             */
/*   Updated: 2019/02/28 12:27:26 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "vectors.h"
#include "rtv1.h"

double	sqr(double value)
{
	return (value * value);
}

int		clamp(double value, int max, int min)
{
	if ((int)value > max)
		return (max);
	if ((int)value < min)
		return (min);
	return ((int)value);
}

int		clampf(double value, double max, double min)
{
	if (value > max)
		return (max);
	if (value < min)
		return (min);
	return (value);
}

int		v3toi(t_v3 v)
{
	int		color;
	uint8_t	*ptr;

	ptr = (uint8_t*)&color;
	ptr[0] = clamp(v.x, 255, 0);
	ptr[1] = clamp(v.y, 255, 0);
	ptr[2] = clamp(v.z, 255, 0);
	return (color);
}

void	pxl_to_img(t_img *img, int x, int y, int color)
{
	img->img_str[x + (y * SCREEN_W)] = color;
}
