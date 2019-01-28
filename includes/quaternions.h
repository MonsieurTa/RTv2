/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:45:49 by wta               #+#    #+#             */
/*   Updated: 2019/01/27 20:11:51 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNIONS_H
# define QUATERNIONS_H

# include "vectors.h"
# include "rtv1.h"

typedef struct	s_quat
{
	double	w;
	double	x;
	double	y;
	double	z;
}				t_quat;

t_quat		q_normalize(t_quat quat);
t_quat		q_mult(t_quat q1, t_quat q2);
t_quat		q_local_rot(t_v3 axis, double angle);
t_quat		q_conj(t_quat q);
t_quat		v3_to_q(t_v3 v);
t_v3		q_to_v3(t_quat q);

#endif
