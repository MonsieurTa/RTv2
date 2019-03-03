/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 17:48:35 by wta               #+#    #+#             */
/*   Updated: 2019/03/03 17:49:27 by wta              ###   ########.fr       */
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
# define BAD_CMRDIR		8
# define SCREEN_W		800
# define SCREEN_H		800
# define K_LEFT			123
# define K_UP			126
# define K_RIGHT		124
# define K_DOWN			125
# define K_A			0
# define K_S			1
# define K_D			2
# define K_Q			12
# define K_W			13
# define K_E			14
# define K_SHIFT		257
# define K_PGUP			116
# define K_PGDOWN		121
# define K_PLUS			69
# define K_MINUS		78
# define NUM_ZERO		82
# define ESC			53
# define AMBT_LIGHT		0
# define SPHERE_LIGHT	1
# define SPHERE			4
# define PLANE			5
# define CYLINDER		6
# define CONE			7
# define PIXEL			16
# define EPS			0.001
# define MAX_THREAD		8

# include "quaternions.h"
# include "vectors.h"

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

typedef struct		s_quad
{
	double			a;
	double			b;
	double			c;
	double			r0;
	double			r1;
	double			det;
}					t_quad;

typedef struct		s_obj
{
	char			type;
	double			radius;
	double			angle;
	double			i;
	t_v3			pos;
	t_v3			dir;
	t_v3			n;
	t_v3			color;
	double			specular;
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
}					t_lst;

typedef struct		s_view
{
	double			fov;
	double			width;
	double			height;
	double			half_w;
	double			half_h;
	t_v3			i;
	t_v3			origin;
}					t_view;

typedef struct		s_cam
{
	t_view			view;
	t_v3			pos;
	t_v3			dir;
	t_v3			up;
	t_v3			right;
	double			x_rot;
	double			y_rot;
	double			z_rot;
}					t_cam;

typedef struct		s_ray
{
	t_v3			pos;
	t_v3			dir;
	double			tmax;
	int				color;
}					t_ray;

typedef struct		s_shading
{
	t_v3			hit;
	t_v3			normal;
	t_ray			light;
	t_v3			color;
	double			t;
	double			i;
}					t_shading;

typedef struct		s_env
{
	t_mlx			mlx;
	t_lst			lights;
	t_lst			objs;
	t_cam			cam;
	t_ray			ray;
	char			shadow;
	int				pxl;
	int				key_pressed;
	int				counter;
	int				spt;
	double			max_w;
}					t_env;

typedef enum		e_error
{
	ERR_NOERROR,
	ERR_ERRNO,
	ERR_BADFMT,
	ERR_MALLOC,
	ERR_GNL
}					t_error;

void				init_cam(t_cam *cam);
void				compute_pos(t_cam *cam);

t_node				*newnode(t_obj obj);
void				init_lst(t_lst *lst);
void				pushback(t_lst *lst, t_node *node);

t_error				read_file(t_env *env, char *file);

t_v3				get_normal(t_ray *ray, t_v3 *hit, t_obj *obj);
double				intersect_cone(t_ray *ray, t_obj *cone);
double				intersect_cylinder(t_ray *ray, t_obj *cylinder);
double				intersect_sphere(t_ray *ray, t_obj *sphere);
double				intersect_plane(t_ray *ray, t_obj *plane);

int					cast_shadow(t_ray *light, t_v3 *hit, t_lst *obj);
void				compute_lights(t_env *env, t_ray *ray,
		t_shading *shading, t_obj *obj);

t_v3				add_color(t_v3 c1, t_v3 c2);
t_v3				multf_color(t_v3 color, double coef);

double				do_quad(t_quad quad);

void				render(t_env *env);
int					draw_all(t_env *env);
int					count_thread(int *counter);

int					key_pressed(int key, void *param);
int					key_released(int key, void *param);
int					apply_key(void *param);
int					close_win(void);

void				pxl_to_img(t_img *img, int x, int y, int color);
int					v3toi(t_v3 v);
int					clampf(double value, double max, double min);
int					clamp(double value, int max, int min);

int					split_n_count(char *str, char c, char ***split);
double				ft_atof(char *str);
int					is_number(char *str);
int					is_float(char *str);
void				delsplit(char **split);
int					is_v3(char **split);
t_v3				split_to_v3(char **split);
t_q					split_to_v4(char **split);
t_error				get_v3(t_obj *obj, int fd, char *str);
t_error				get_double(t_obj *obj, int fd, char *str);

t_error				get_sphere(t_env *env, int fd);
t_error				get_plane(t_env *env, int fd);
t_error				get_cylinder(t_env *env, int fd);
t_error				get_cone(t_env *env, int fd);
t_error				get_light(t_env *env, int fd);
t_error				get_light_type(t_obj *light, int fd);
t_error				get_camera(t_env *env, int fd);

t_error				get_v3(t_obj *obj, int fd, char *str);
t_error				get_v3_spec(t_obj *obj, char *str, char **split, int cnt);
void				err_handler(t_error err_id);

void				lst_destroy(t_lst *lst);

#endif
