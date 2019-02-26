/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 06:11:25 by wta               #+#    #+#             */
/*   Updated: 2019/02/26 17:50:59 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <math.h>
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

t_error	get_v3(t_obj *obj, int fd, char *str)
{
	char	**split;
	char	*line;
	int		cnt;
	int		len;
	t_error	err_id;

	err_id = ERR_NOERROR;
	if (get_next_line(fd, &line) <= 0)
		return (ERR_BADFMT);
	len = ft_strlen(str);
	if (ft_strnequ(line, str, len) == 0)
		err_id = ERR_BADFMT;
	if (err_id == ERR_NOERROR)
	{
		if ((cnt = split_n_count(line + len, ',', &split)) > 0)
		{
			if (cnt != 3 || is_v3(split) == 0)
				err_id = ERR_BADFMT;
			else if (ft_strequ(str, "pos="))
				obj->pos = split_to_v3(split);
			else if (ft_strequ(str, "color="))
				obj->color = split_to_v3(split);
			else if (ft_strequ(str, "normal="))
				obj->n = v3normalize(split_to_v3(split));
			else if (ft_strequ(str, "dir="))
				obj->dir = v3normalize(split_to_v3(split));
			else
				err_id = ERR_BADFMT;
			delsplit(split);
		}
	}
	free(line);
	return (err_id);
}



t_error	get_phong(t_obj *obj, int fd, char *str)
{
	char	**split;
	char	*line;
	int		len;
	int		cnt;
	t_error	err_id;

	err_id = ERR_NOERROR;
	if (get_next_line(fd, &line) <= 0)
		return (ERR_BADFMT);
	len = ft_strlen(str);
	if (ft_strnequ(line, str, len) == 0)
		err_id = ERR_BADFMT;
	if (err_id == ERR_NOERROR)
	{
		if ((cnt = split_n_count(line + len, ',', &split)) > 0)
		{
			if (cnt != 4 || is_v3(split) == 0)
			{
				err_id = ERR_BADFMT;
			}
			else if (ft_strequ(str, "phong=") == 1)
				obj->phong = split_to_v4(split);
			else
				err_id = ERR_BADFMT;
			delsplit(split);
		}
	}
	free(line);
	return (err_id);
}

t_error	get_double(t_obj *obj, int fd, char *str)
{
	char	*line;
	int		len;
	t_error	err_id;

	err_id = ERR_NOERROR;
	if (get_next_line(fd, &line) <= 0)
		return (ERR_BADFMT);
	len = ft_strlen(str);
	if (ft_strnequ(line, str, len) == 0)
		err_id = ERR_BADFMT;
	if (err_id == ERR_NOERROR)
	{
		if (is_float(line + len) == 0 && is_number(line + len) == 0)
			err_id = ERR_BADFMT;
		else if (ft_strequ(str, "radius="))
			obj->radius = ft_atof(line + len);
		else if (ft_strequ(str, "angle="))
			obj->angle = ft_atof(line + len) * M_PI / 180;
		else if (ft_strequ(str, "i="))
			obj->i = ft_atof(line + len);
	}
	free(line);
	return (err_id);
}

t_error	get_sphere(t_env *env, int fd)
{
	t_node	*node;
	char	*line;
	t_obj	sphere;
	t_error	err_id;

	sphere.type = SPHERE;
	line = NULL;
	err_id = ERR_NOERROR;
	err_id = get_v3(&sphere, fd, "pos=");
	if (err_id == ERR_NOERROR)
		err_id = get_v3(&sphere, fd, "color=");
	if (err_id == ERR_NOERROR)
		err_id = get_double(&sphere, fd, "radius=");
	if (err_id == ERR_NOERROR)
		err_id = get_phong(&sphere, fd, "phong=");
	if (err_id == ERR_NOERROR)
	{
		node = newnode(sphere);
		if (node == NULL)
			return (ERR_MALLOC);
		pushback(&env->objs, node);
	}
	return (err_id);
}

t_error	get_plane(t_env *env, int fd)
{
	t_node	*node;
	char	*line;
	t_obj	plane;
	t_error	err_id;

	plane.type = PLANE;
	line = NULL;
	err_id = get_v3(&plane, fd, "pos=");
	if (err_id == ERR_NOERROR)
		err_id = get_v3(&plane, fd, "normal=");
	if (err_id == ERR_NOERROR)
		err_id = get_v3(&plane, fd, "color=");
	if (err_id == ERR_NOERROR)
		err_id = get_phong(&plane, fd, "phong=");
	if (err_id == ERR_NOERROR)
	{
		node = newnode(plane);
		if (node == NULL)
			return (ERR_MALLOC);
		pushback(&env->objs, node);
	}
	return (err_id);
}

t_error	get_cylinder(t_env *env, int fd)
{
	t_node	*node;
	char	*line;
	t_obj	cylinder;
	t_error	err_id;

	cylinder.type = CYLINDER;
	line = NULL;
	err_id = get_v3(&cylinder, fd, "pos=");
	if (err_id == ERR_NOERROR)
		err_id = get_double(&cylinder, fd, "radius=");
	if (err_id == ERR_NOERROR)
		err_id = get_v3(&cylinder, fd, "dir=");
	if (err_id == ERR_NOERROR)
		err_id = get_v3(&cylinder, fd, "color=");
	if (err_id == ERR_NOERROR)
		err_id = get_phong(&cylinder, fd, "phong=");
	if (err_id == ERR_NOERROR)
	{
		node = newnode(cylinder);
		if (node == NULL)
			return (ERR_MALLOC);
		pushback(&env->objs, node);
	}
	return (err_id);
}

t_error	get_cone(t_env *env, int fd)
{
	t_node	*node;
	char	*line;
	t_obj	cone;
	t_error	err_id;

	cone.type = CONE;
	line = NULL;
	err_id = get_v3(&cone, fd, "pos=");
	if (err_id == ERR_NOERROR)
		err_id = get_double(&cone, fd, "angle=");
	if (err_id == ERR_NOERROR)
		err_id = get_v3(&cone, fd, "dir=");
	if (err_id == ERR_NOERROR)
		err_id = get_v3(&cone, fd, "color=");
	if (err_id == ERR_NOERROR)
		err_id = get_phong(&cone, fd, "phong=");
	if (err_id == ERR_NOERROR)
	{
		node = newnode(cone);
		if (node == NULL)
			return (ERR_MALLOC);
		pushback(&env->objs, node);
	}
	return (err_id);
}

t_error	get_light(t_env *env, int fd)
{
	t_node	*node;
	char	*line;
	t_obj	light;
	t_error	err_id;

	light.type = SPHERE_LIGHT;
	line = NULL;
	err_id = get_v3(&light, fd, "pos=");
	if (err_id == ERR_NOERROR)
		err_id = get_double(&light, fd, "i=");
	if (err_id == ERR_NOERROR)
		err_id = get_v3(&light, fd, "color=");
	if (err_id == ERR_NOERROR)
	{
		node = newnode(light);
		if (node == NULL)
			return (ERR_MALLOC);
		pushback(&env->lights, node);
	}
	return (err_id);
}

t_error	get_cam_pos(t_cam *cam, int fd, char *str)
{
	char	**split;
	char	*line;
	int		cnt;
	int		len;
	t_error	err_id;

	err_id = ERR_NOERROR;
	if (get_next_line(fd, &line) <= 0)
		return (ERR_BADFMT);
	len = ft_strlen(str);
	if (ft_strnequ(line, str, len) == 0)
		err_id = ERR_BADFMT;
	if (err_id == ERR_NOERROR)
	{
		if ((cnt = split_n_count(line + len, ',', &split)) > 0)
		{
			if (cnt != 3 || is_v3(split) == 0)
				err_id = ERR_BADFMT;
			else if (ft_strequ(str, "pos="))
				cam->pos = split_to_v3(split);
			else
				err_id = ERR_BADFMT;
			delsplit(split);
		}
	}
	free(line);
	return (err_id);
}

t_error	get_cam_rot(t_cam *cam, int fd, char *str)
{
	char	*line;
	int		len;
	t_error	err_id;

	err_id = ERR_NOERROR;
	if (get_next_line(fd, &line) <= 0)
		return (ERR_BADFMT);
	len = ft_strlen(str);
	if (ft_strnequ(line, str, len) == 0)
		err_id = ERR_BADFMT;
	if (err_id == ERR_NOERROR)
	{
		if (is_float(line + len) == 0 && is_number(line + len) == 0)
			err_id = ERR_BADFMT;
		else if (ft_strequ(str, "xrot="))
			cam->x_rot = ft_atof(line + len);
		else if (ft_strequ(str, "yrot="))
			cam->y_rot = ft_atof(line + len);
		else if (ft_strequ(str, "zrot="))
			cam->z_rot = ft_atof(line + len);
	}
	free(line);
	return (err_id);
}

t_error	get_camera(t_env *env, int fd)
{
	char	*line;
	t_error	err_id;

	line = NULL;
	err_id = get_cam_pos(&env->cam, fd, "pos=");
	if (err_id == ERR_NOERROR)
		err_id = get_cam_rot(&env->cam, fd, "xrot=");
	if (err_id == ERR_NOERROR)
		err_id = get_cam_rot(&env->cam, fd, "yrot=");
	if (err_id == ERR_NOERROR)
		err_id = get_cam_rot(&env->cam, fd, "zrot=");
	return (err_id);
}

t_error	get_obj(t_env *env, int fd)
{
	char	*line;
	int		gnl_ret;
	t_error	err_id;

	line = NULL;
	err_id = ERR_NOERROR;
	while ((gnl_ret = get_next_line(fd, &line)) > 0)
	{
		if (ft_strnequ(line, "type=", 5) == 0)
			err_id = ERR_BADFMT;
		if (err_id == ERR_NOERROR)
		{
			if (ft_strequ(line + 5, "sphere") == 1)
				err_id = get_sphere(env, fd);
			if (ft_strequ(line + 5, "plane") == 1)
				err_id = get_plane(env, fd);
			if (ft_strequ(line + 5, "cylinder") == 1)
				err_id = get_cylinder(env, fd);
			if (ft_strequ(line + 5, "cone") == 1)
			   err_id = get_cone(env, fd);
			if (ft_strequ(line + 5, "light") == 1)
			   err_id = get_light(env, fd);
			if (ft_strequ(line + 5, "camera") == 1)
			   err_id = get_camera(env,fd);
		}
	}
	free(line);
	return (err_id);
}


t_error	read_file(t_env *env, char *file)
{
	t_error	err_id;
	char	*line;
	int		fd;

	err_id = ERR_NOERROR;
	fd = open(file, O_RDONLY);
	line = NULL;
	err_id = get_obj(env, fd);
	close(fd);
	return (err_id);
}
