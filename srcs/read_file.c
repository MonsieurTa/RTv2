/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 06:11:25 by wta               #+#    #+#             */
/*   Updated: 2019/03/02 20:30:44 by wta              ###   ########.fr       */
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
			id = get_spec_obj(env, fd, line);
		ft_strdel(&line);
	}
	if (gnl_ret == -1)
		id = ERR_GNL;
	return (id);
}

t_error	is_valid_file(int fd)
{
	char	buf[6];
	int		ret;

	if ((ret = read(fd, buf, 5)) < 5)
		return (ERR_BADFMT);
	buf[ret] = '\0';
	if (ft_strequ(buf, "rtv1\n") == 0)
		return (ERR_BADFMT);
	return (ERR_NOERROR);
}

t_error	read_file(t_env *env, char *file)
{
	t_error	id;
	char	*line;
	int		fd;

	id = ERR_NOERROR;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (ERR_ERRNO);
	id = is_valid_file(fd);
	line = NULL;
	if (id == ERR_NOERROR)
		id = get_obj(env, fd);
	close(fd);
	return (id);
}
