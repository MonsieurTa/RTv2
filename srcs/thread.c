/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 02:41:55 by wta               #+#    #+#             */
/*   Updated: 2019/03/05 03:28:12 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "rtv1.h"

int		draw_all(t_env *env)
{
	pthread_t	threads[MAX_THREAD];
	int			index;

	env->counter = 0;
	index = -1;
	while (++index < MAX_THREAD)
		if ((pthread_create(&threads[index], NULL,
						(void*)render, env) == -1))
			return (0);
	index = -1;
	while (++index < MAX_THREAD)
		if ((pthread_join(threads[index], NULL)) != 0)
			return (0);
	return (1);
}

int		count_thread(int *counter)
{
	int	count;
	int	i;

	count = 0;
	i = 1;
	while (*counter & i)
	{
		i <<= 1;
		count++;
	}
	*counter |= i;
	return (count);
}
