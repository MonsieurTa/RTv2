/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternions_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 01:47:19 by wta               #+#    #+#             */
/*   Updated: 2019/02/12 01:47:47 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternions.h"

t_v3	q_to_v3(t_q q)
{
	t_v3	v;

	v.x = q.x;
	v.y = q.y;
	v.z = q.z;
	return (v);
}