/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 19:31:44 by wta               #+#    #+#             */
/*   Updated: 2019/01/22 02:12:21 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "vectors.h"
#include "rtv1.h"

void	init_cam(t_cam *cam)
{
	cam->pos = (t_vec3){0., 0., -10.};
	cam->dir = (t_vec3){0., 0., 1.};
	cam->up = (t_vec3){0., 1., 0.};
	cam->right = (t_vec3){1., 0., 0.};
	cam->fov = M_PI / 2;
}

void	look_at(t_cam *cam, t_vec3 from, t_vec3 to)
{
	t_vec3	tmp;

	cam->dir = vec3_normalize(vec3_sub(from, to));
	tmp = (t_vec3){0., 1., 0.};
	cam->right = vec3_normalize(vec3_cross(vec3_normalize(tmp), cam->dir));
	cam->up = vec3_cross(cam->dir, cam->right);
	cam->pos = from;
}
