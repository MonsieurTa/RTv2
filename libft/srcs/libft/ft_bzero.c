/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 02:27:46 by wta               #+#    #+#             */
/*   Updated: 2019/02/27 16:07:04 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	s = s + n;
	while (n >= sizeof(__uint128_t))
	{
		n -= sizeof(__uint128_t);
		s -= sizeof(__uint128_t);
		*(__uint128_t*)(s) = 0;
	}
	while (n >= sizeof(long long))
	{
		n -= sizeof(long long);
		s -= sizeof(long long);
		*(unsigned long long*)(s) = 0;
	}
	while (n >= sizeof(short))
	{
		n -= sizeof(short);
		s -= sizeof(short);
		*(unsigned short*)(s) = 0;
	}
	if (n > 0)
		*(char*)--s = 0;
}
