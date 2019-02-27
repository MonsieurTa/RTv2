/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file_helper3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 13:01:12 by wta               #+#    #+#             */
/*   Updated: 2019/02/27 13:19:54 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "rtv1.h"

t_error	get_cam_pos(t_cam *cam, int fd, char *str)
{
	char	**split;
	char	*line;
	int		cnt;
	int		len;
	t_error	id;

	id = ERR_NOERROR;
	if (get_next_line(fd, &line) <= 0)
		return (ERR_BADFMT);
	len = ft_strlen(str);
	if (ft_strnequ(line, str, len) == 0)
		id = ERR_BADFMT;
	if (id == ERR_NOERROR && (cnt = split_n_count(line + len, ',', &split)) > 0)
	{
		if (cnt != 3 || is_v3(split) == 0)
			id = ERR_BADFMT;
		else if (ft_strequ(str, "pos="))
			cam->pos = split_to_v3(split);
		else
			id = ERR_BADFMT;
		delsplit(split);
	}
	free(line);
	return (id);
}

t_error	get_cam_rot(t_cam *cam, int fd, char *str)
{
	char	*line;
	int		len;
	t_error	id;

	id = ERR_NOERROR;
	if (get_next_line(fd, &line) <= 0)
		return (ERR_BADFMT);
	len = ft_strlen(str);
	if (ft_strnequ(line, str, len) == 0)
		id = ERR_BADFMT;
	if (id == ERR_NOERROR)
	{
		if (is_float(line + len) == 0 && is_number(line + len) == 0)
			id = ERR_BADFMT;
		else if (ft_strequ(str, "xrot="))
			cam->x_rot = ft_atof(line + len);
		else if (ft_strequ(str, "yrot="))
			cam->y_rot = ft_atof(line + len);
		else if (ft_strequ(str, "zrot="))
			cam->z_rot = ft_atof(line + len);
	}
	free(line);
	return (id);
}

t_error	get_camera(t_env *env, int fd)
{
	char	*line;
	t_error	id;

	line = NULL;
	id = get_cam_pos(&env->cam, fd, "pos=");
	if (id == ERR_NOERROR)
		id = get_cam_rot(&env->cam, fd, "xrot=");
	if (id == ERR_NOERROR)
		id = get_cam_rot(&env->cam, fd, "yrot=");
	if (id == ERR_NOERROR)
		id = get_cam_rot(&env->cam, fd, "zrot=");
	return (id);
}

t_error	get_v3_spec(t_obj *obj, char *str, char **split, int cnt)
{
	t_error	id;

	id = ERR_NOERROR;
	if (cnt != 3 || is_v3(split) == 0)
		id = ERR_BADFMT;
	else if (ft_strequ(str, "pos="))
		obj->pos = split_to_v3(split);
	else if (ft_strequ(str, "color="))
		obj->color = split_to_v3(split);
	else if (ft_strequ(str, "normal="))
		obj->n = v3normalize(split_to_v3(split));
	else if (ft_strequ(str, "dir="))
		obj->dir = v3normalize(split_to_v3(split));
	else
		id = ERR_BADFMT;
	return (id);
}

t_error	get_v3(t_obj *obj, int fd, char *str)
{
	char	**split;
	char	*line;
	int		cnt;
	int		len;
	t_error	id;

	id = ERR_NOERROR;
	if (get_next_line(fd, &line) <= 0)
		return (ERR_BADFMT);
	len = ft_strlen(str);
	if (ft_strnequ(line, str, len) == 0)
		id = ERR_BADFMT;
	if (id == ERR_NOERROR)
	{
		if ((cnt = split_n_count(line + len, ',', &split)) > 0)
		{
			id = get_v3_spec(obj, str, split, cnt);
			delsplit(split);
		}
	}
	free(line);
	return (id);
}
