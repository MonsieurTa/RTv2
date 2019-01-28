/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:45:49 by wta               #+#    #+#             */
/*   Updated: 2019/01/28 18:29:13 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNIONS_H
# define QUATERNIONS_H

# include "vectors.h"
# include "utils.h"

typedef struct	s_q
{
	double	w;
	double	x;
	double	y;
	double	z;
}				t_q;

t_q		q_normalize(t_q q);
t_q		q_mult(t_q q1, t_q q2);
t_q		q_local_rot(t_v3 axis, double angle);
t_q		q_conj(t_q q);
t_q		v3_to_q(t_v3 v);
t_v3	q_to_v3(t_q q);

#endif
