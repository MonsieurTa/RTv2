/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/03 14:15:36 by wta               #+#    #+#             */
/*   Updated: 2018/11/05 14:55:12 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_toupper(int c)
{
	return ((c >= 'a' && c <= 'z') ? c - 32 : c);
}
