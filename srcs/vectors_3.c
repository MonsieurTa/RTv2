/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 01:26:01 by wta               #+#    #+#             */
/*   Updated: 2019/03/27 22:30:37 by williamta        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vectors.h"

t_v3	v3project(t_v3 v, t_v3 w)
{
	t_v3	vector;
	double	scalar;

	scalar = v3dot(&v, &w) / v3dot(&w, &w);
	vector = v3multf(w, scalar);
	return (vector);
}
