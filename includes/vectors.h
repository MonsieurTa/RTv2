/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:19:55 by wta               #+#    #+#             */
/*   Updated: 2019/03/27 22:25:56 by williamta        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct	s_v3
{
	double		x;
	double		y;
	double		z;
}				t_v3;

t_v3			v3add(t_v3 v, t_v3 w);
t_v3			v3sub(t_v3 v, t_v3 w);
t_v3			v3mult(t_v3 v, t_v3 w);
t_v3			v3multf(t_v3 v, double scalar);
t_v3			v3cross(t_v3 v, t_v3 w);
t_v3			v3normalize(t_v3 v);
t_v3			v3project(t_v3 v, t_v3 w);
double			v3cos(t_v3 v, t_v3 w);
double			v3normf(t_v3 v, double scalar);
double			v3norm(t_v3 v);
double			v3dot(t_v3 *v, t_v3 *w);

#endif
