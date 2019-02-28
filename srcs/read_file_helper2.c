/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_helper2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 12:55:24 by wta               #+#    #+#             */
/*   Updated: 2019/02/28 14:29:34 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/includes/libft.h"
#include "rtv1.h"

t_error	get_sphere(t_env *env, int fd)
{
	t_node	*node;
	char	*line;
	t_obj	sphere;
	t_error	err_id;

	ft_bzero(&sphere, sizeof(t_obj));
	sphere.type = SPHERE;
	line = NULL;
	err_id = ERR_NOERROR;
	err_id = get_v3(&sphere, fd, "pos=");
	if (err_id == ERR_NOERROR)
		err_id = get_v3(&sphere, fd, "color=");
	if (err_id == ERR_NOERROR)
		err_id = get_double(&sphere, fd, "radius=");
	if (err_id == ERR_NOERROR)
		err_id = get_double(&sphere, fd, "specular=");
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

	ft_bzero(&plane, sizeof(t_obj));
	plane.type = PLANE;
	line = NULL;
	err_id = get_v3(&plane, fd, "pos=");
	if (err_id == ERR_NOERROR)
		err_id = get_v3(&plane, fd, "normal=");
	if (err_id == ERR_NOERROR)
		err_id = get_v3(&plane, fd, "color=");
	if (err_id == ERR_NOERROR)
		err_id = get_double(&plane, fd, "specular=");
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

	ft_bzero(&cylinder, sizeof(t_obj));
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
		err_id = get_double(&cylinder, fd, "specular=");
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

	ft_bzero(&cone, sizeof(t_obj));
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
		err_id = get_double(&cone, fd, "specular=");
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

	ft_bzero(&light, sizeof(t_obj));
	light.type = SPHERE_LIGHT;
	line = NULL;
	node = NULL;
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
