/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:19:55 by wta               #+#    #+#             */
/*   Updated: 2019/01/22 00:35:56 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct	s_int2
{
	int			x;
	int			y;
}				t_int2;

typedef struct	s_vec3
{
	double		x;
	double		y;
	double		z;
}				t_vec3;

t_vec3			vec3_add(t_vec3 v, t_vec3 w);
t_vec3			vec3_sub(t_vec3 v, t_vec3 w);
t_vec3			vec3_mult(t_vec3 v, t_vec3 w);
t_vec3			vec3_multf(t_vec3 v, double scalar);
t_vec3			vec3_cross(t_vec3 v, t_vec3 w);
t_vec3			vec3_normalize(t_vec3 v);
double			vec3_cos(t_vec3 v, t_vec3 w);
double			vec3_normf(t_vec3 v, double scalar);
double			vec3_norm(t_vec3 v);
double			vec3_dot(t_vec3 v, t_vec3 w);

#endif
