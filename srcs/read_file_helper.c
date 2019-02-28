/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:38:40 by wta               #+#    #+#             */
/*   Updated: 2019/02/28 14:55:19 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "../libft/includes/libft.h"
#include "rtv1.h"

t_v3	split_to_v3(char **split)
{
	t_v3	v;

	v.x = ft_atof(split[0]);
	v.y = ft_atof(split[1]);
	v.z = ft_atof(split[2]);
	return (v);
}

t_q		split_to_v4(char **split)
{
	t_q	q;

	q.w = ft_atof(split[0]);
	q.x = ft_atof(split[1]);
	q.y = ft_atof(split[2]);
	q.z = ft_atof(split[3]);
	return (q);
}

t_error	set_double(t_obj *obj, char *line, char *str, int len)
{
	t_error	id;

	id = ERR_NOERROR;
	if (is_float(line + len) == 0 && is_number(line + len) == 0)
		id = ERR_BADFMT;
	else if (ft_strequ(str, "radius="))
		obj->radius = fabs(ft_atof(line + len));
	else if (ft_strequ(str, "angle="))
		obj->angle = ft_atof(line + len) * M_PI / 180;
	else if (ft_strequ(str, "i="))
		obj->i = fabs(ft_atof(line + len));
	else if (ft_strequ(str, "specular="))
		obj->specular = fabs(ft_atof(line + len));
	return (id);
}

t_error	get_double(t_obj *obj, int fd, char *str)
{
	char	*line;
	int		len;
	t_error	id;

	id = ERR_NOERROR;
	line = NULL;
	if (get_next_line(fd, &line) <= 0)
		return (ERR_BADFMT);
	len = ft_strlen(str);
	if (ft_strnequ(line, str, len) == 0)
		id = ERR_BADFMT;
	if (id == ERR_NOERROR)
		id = set_double(obj, line, str, len);
	ft_strdel(&line);
	return (id);
}
