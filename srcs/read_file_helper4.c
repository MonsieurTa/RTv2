/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_helper4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 13:48:57 by wta               #+#    #+#             */
/*   Updated: 2019/03/04 14:11:37 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "rtv1.h"

t_error	get_light_type(t_obj *light, int fd)
{
	t_error	id;
	char	*line;

	id = ERR_NOERROR;
	line = NULL;
	if (get_next_line(fd, &line) <= 0)
		return (ERR_BADFMT);
	if (ft_strequ(line, "spherical") == 1)
		light->type = SPHERE_LIGHT;
	else if (ft_strequ(line, "ambient") == 1)
		light->type = AMBT_LIGHT;
	else
		id = ERR_BADFMT;
	ft_strdel(&line);
	return (id);
}
