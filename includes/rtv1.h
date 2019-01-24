/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 13:26:06 by wta               #+#    #+#             */
/*   Updated: 2019/01/24 01:00:10 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# define RD_ERR			2
# define BAD_FMT		3
# define MALLOC_ERR		4
# define GNL_ERR		5
# define READ_ERR		6
# define MLX_ERR		7
# define SCREEN_W		1200
# define SCREEN_H		720
# define K_LEFT			123
# define K_UP			126
# define K_RIGHT		124
# define K_DOWN			125
# define K_A			0
# define K_D			2
# define K_SHIFT		257
# define K_PLUS			69
# define K_MINUS		78
# define NUM_ZERO		82
# define OPT_FLOOR		83
# define ESC			53
# define DST_LIGHT		0
# define SPHERE_LIGHT	1
# define DIR_LIGHT		2
# define SPHERE			3
# define PLANE			4

#include "vectors.h"

typedef unsigned char	t_uchar;

typedef struct		s_img
{
	void			*img_ptr;
	int				*img_str;
	int				width;
	int				height;
	int				bpp;
	int				sizel;
	int				endian;
}					t_img;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
}					t_mlx;

typedef struct		s_color
{
	t_uchar			r;
	t_uchar			g;
	t_uchar			b;
}					t_color;

typedef struct		s_comp
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			up;
	t_vec3			right;
}					t_comp;

typedef struct		s_ray
{
	t_vec3			pos;
	t_vec3			dir;
}					t_ray;

typedef struct		s_mat
{
	t_vec3			n;
	t_vec3			hit;
	double			t;
	double			tmax;
	int				color;
	int				reflect;
}					t_mat;

typedef struct		s_cam
{
	t_vec3			pos;
	t_vec3			dir;
	t_vec3			up;
	t_vec3			right;
	t_ray			ray;
	double			fov;
}					t_cam;

typedef struct		s_quad
{
	double			a;
	double			b;
	double			c;
	double			r0;
	double			r1;
	double			det;
}					t_quad;

typedef struct		s_view
{
	t_vec3			pos;
	double			width;
	double			height;
	double			dist;
}					t_view;

typedef struct		s_obj
{
	char			type;
	t_vec3			pos;
	t_color			color;
	double			radius;
	double			intensity;
}					t_obj;

typedef	struct		s_node
{
	struct s_node	*next;
	t_obj			obj;
}					t_node;

typedef struct		s_lst
{
	t_node			*head;
	t_node			*tail;
	t_node			*node;
}					t_lst;

typedef struct		s_scene
{
	t_cam			cam;
	t_view			view;
	t_lst			objs;
	t_lst			lights;
	t_mat			mat;
}					t_scene;

typedef struct		s_env
{
	t_mlx			mlx;
	t_scene			scene;
	int				key_pressed;
}					t_env;

t_obj				new_light(t_vec3 pos, double intensity, int type, t_color color);
t_obj				new_sphere(t_vec3 pos, double radius, t_color color);
void				pushback(t_lst *lst, t_node *node);
void				init_lst(t_lst *lst);
t_node				*newnode(t_obj obj);

void				init_cam(t_cam *cam);
void				set_view(t_env *env);
t_comp				look_at(t_vec3 from, t_vec3 to);

double				do_quad(t_quad quad);

void				render(t_mlx *mlx, t_scene *scene);

int					key_pressed(int key, void *param);
int					key_released(int key, void *param);
int					close_win(void);

void				err_handler(int err_id);

#endif
