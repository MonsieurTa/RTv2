/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 06:11:25 by wta               #+#    #+#             */
/*   Updated: 2019/02/27 13:27:41 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <math.h>
#include "../libft/includes/libft.h"
#include "rtv1.h"

t_error	get_spec_obj(t_env *env, int fd, char *line)
{
	t_error	id;

	id = ERR_NOERROR;
	if (ft_strequ(line + 5, "sphere") == 1)
		id = get_sphere(env, fd);
	if (ft_strequ(line + 5, "plane") == 1)
		id = get_plane(env, fd);
	if (ft_strequ(line + 5, "cylinder") == 1)
		id = get_cylinder(env, fd);
	if (ft_strequ(line + 5, "cone") == 1)
		id = get_cone(env, fd);
	if (ft_strequ(line + 5, "light") == 1)
		id = get_light(env, fd);
	if (ft_strequ(line + 5, "camera") == 1)
		id = get_camera(env, fd);
	return (id);
}

t_error	get_obj(t_env *env, int fd)
{
	char	*line;
	int		gnl_ret;
	t_error	id;

	line = NULL;
	id = ERR_NOERROR;
	while ((gnl_ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_strnequ(line, "type=", 5) == 0)
			id = ERR_BADFMT;
		if (id == ERR_NOERROR)
			get_spec_obj(env, fd, line);
		ft_strdel(&line);
	}
	free(line);
	return (id);
}

t_error	read_file(t_env *env, char *file)
{
	t_error	id;
	char	*line;
	int		fd;

	id = ERR_NOERROR;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (ERR_ERRNO);
	line = NULL;
	id = get_obj(env, fd);
	close(fd);
	return (id);
}
