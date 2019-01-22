/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:26:06 by wta               #+#    #+#             */
/*   Updated: 2019/01/22 20:14:04 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define RD_ERR		2
# define BAD_FMT	3
# define MALLOC_ERR	4
# define GNL_ERR	5
# define READ_ERR	6
# define MLX_ERR	7
# define SCREEN_W	1200
# define SCREEN_H	720
# define K_LEFT		123
# define K_UP		126
# define K_RIGHT	124
# define K_DOWN		125
# define K_A		0
# define K_D		2
# define K_SHIFT	257
# define K_PLUS		69
# define K_MINUS	78
# define NUM_ZERO	82
# define OPT_FLOOR	83
# define ESC		53

#include "vectors.h"

typedef struct	s_img
{
	void		*img_ptr;
	int			*img_str;
	int			width;
	int			height;
	int			bpp;
	int			sizel;
	int			endian;
}				t_img;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
}				t_mlx;

typedef struct	s_comp
{
	t_vec3		pos;
	t_vec3		dir;
	t_vec3		up;
	t_vec3		right;
}				t_comp;

typedef struct	s_sphere
{
	t_vec3		pos;
	double		radius;
	int			color;
}				t_sphere;

typedef struct	s_ray
{
	t_vec3		pos;
	t_vec3		dir;
}				t_ray;

typedef struct	s_cam
{
	t_vec3		pos;
	t_vec3		dir;
	t_vec3		up;
	t_vec3		right;
	t_ray		ray;
	double		fov;
}				t_cam;

typedef struct	s_quad
{
	double		a;
	double		b;
	double		c;
	double		r0;
	double		r1;
	double		det;
}				t_quad;

typedef struct	s_view
{
	double		width;
	double		height;
	double		dist;
}				t_view;

typedef struct	s_info
{
	t_mlx		mlx;
	t_cam		cam;
	t_view		view;
	int			key_pressed;
}				t_info;

void			init_cam(t_cam *cam);
void			set_view(t_info *info);
t_comp			look_at(t_vec3 from, t_vec3 to);

double			do_quad(t_quad quad);

void			render(t_img *img, t_cam *cam, t_view *view);

int				key_pressed(int key, void *param);
int				key_released(int key, void *param);
int				close_win(void);

void			err_handler(int err_id);

#endif
