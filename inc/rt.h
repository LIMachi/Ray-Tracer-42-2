/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 00:05:50 by hmartzol          #+#    #+#             */
/*   Updated: 2017/04/13 06:45:10 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <rt_incs.h>
# include <rt_types.h>
# include <rt_cl.h>
# define OCL_SOURCE_PATH "./scl/raytracer.cl"
# define NONE 0
# define UPD 1

typedef enum		e_prim_type
{
	INVALID = -1, SPHERE = 0, PLANE = 1, CONE = 2, CYLINDER = 3, PARABOLOID = 4
}					t_prim_type;

typedef enum		e_pert_type
{
	SINE = 1, CHECKERBOARD = 2
}					t_pert_type;

typedef enum		e_color_filter
{
	SEPIA = 1, GRAYSCALE = 2, CARTOON = 3
}					t_color_filter;

typedef struct		s_perturbation
{
	cl_float		normal;
	t_pert_type		color;
}					t_perturbation;

typedef struct		s_texture
{
	cl_ulong		info_index;
	cl_float2		stretch;
	cl_float2		offset;
}					t_texture;

typedef struct		s_material
{
	cl_float4		color;
	cl_float		diffuse;
	cl_float		specular;
	cl_float		reflection;
	t_perturbation	perturbation;
	t_texture		texture;
}					t_material;

typedef struct		s_img_info
{
	cl_ulong		index;
	cl_int2			size;
}					t_img_info;

typedef struct		s_pair
{
	char			*name;
	cl_ulong		index;
}					t_pair;

typedef struct		s_material_holder
{
	int				nb_materials;
	char			**name;
	t_material		*materials;
}					t_material_holder;

typedef struct		s_textures_holder
{
	int				nb_info;
	char			**path;
	t_img_info		*info;
	int				total_raw_size;
	cl_int			*raw_bmp;
}					t_textures_holder;

typedef struct		s_camera
{
	cl_float4		pos;
	cl_float4		dir;
	cl_float4		up;
	cl_float4		right;
	cl_float4		vpul;
	cl_float2		vp_size;
	float			dist;
	t_quaternion	orientation;
	t_vector		origin_dir;
	t_vector		origin_up;
	t_vector		origin_right;
}					t_camera;

typedef struct		s_limit
{
	cl_int			relative;
	cl_float4		high;
	cl_float4		low;
}					t_limit;

typedef struct		s_primitive
{
	t_prim_type		type;
	cl_float4		position;
	cl_float4		direction;
	cl_float		radius;
	cl_uint			material;
	t_limit			limit;
}					t_primitive;

typedef struct		s_light
{
	cl_float4		position;
	cl_float4		color;
}					t_light;

typedef struct		s_argn
{
	cl_int2			screen_size;
	cl_int			nb_objects;
	cl_int			nb_lights;
	cl_int			map_primitives;
	cl_float		ambient;
	cl_float		direct;
	cl_int			antialias;
	cl_int			bounce_depth;
	t_color_filter	filter;
	cl_int			stereoscopy;
	t_texture		skybox;
	cl_int			nb_info;
	cl_int			nb_materials;
}					t_argn;

typedef struct		s_mouse
{
	int				is_select;
	double			x;
	double			y;
}					t_mouse;

typedef struct		s_cmd
{
	char			*scene;
	char			*output;
	int				progress_bar_toggle;
}					t_cmd;

typedef struct		s_keys
{
	int				ctrl;
	int				updated;
	int				cursor;
}					t_keys;

typedef struct		s_key
{
	int		keycode;
	int		pressed;
	void	(*press)(t_env *, int);
	void	(*repeat)(t_env *, int);
	void	(*release)(t_env *, int);
}					t_key;

typedef struct		s_ctx_glfw
{
	GLFWwindow		*win;
	char			*win_name;
	int				fps;
	t_key			*keys;
	int				nkeys;
	t_key			*mkeys;
	int				nmkeys;
	t_cl_ctx		cl_ctx;
	cl_mem			cl_tex;
	GLuint			tex;
	GLuint			program;
	GLuint			vao;
	t_cl_kernel		*render;
}					t_ctx_glfw;

typedef struct		s_env
{
	t_light				*lights;
	t_primitive			*prim;
	t_material_holder	materials;
	t_textures_holder	textures;
	t_cmd				cmd;
	t_argn				argn;
	t_camera			cam;
	t_ubmp				out;
	t_ubmp				prim_map;
	t_keys				keys;
	t_mouse				mouse;
	t_point				window;
	t_ctx_glfw			glfw;
}					t_env;

/*DOOMED */t_primitive			**prim(void);
/*DOOMED */t_argn				*argn(void);
/*DOOMED */t_ubmp				*out(void);
/*DOOMED */t_ubmp				*prim_map(void);
/*DOOMED */t_cmd				*cmd(void);
/*DOOMED */t_light				**lights(void);
/*DOOMED */t_textures_holder	*textures_holder(void);
/*DOOMED */t_material_holder	*materials(void);
/*DOOMED */t_camera			*cam(void);


void				die(int err, char *msg, const char *err_log, ...);

void				rt(t_env *e);
void				update(t_env *e);

void				save(t_env *e, int keycode);
t_env				*glfw_env(t_env *e);
GLFWwindow			*glfw_init(t_env *e, char *name, int w, int h);
void				key_callback(GLFWwindow* win, int key, int scan,
	int action, int mods);
void				mouse_callback(GLFWwindow* window, double x, double y);

void				set_keys(t_env *e);
void				handle_keys(t_key *keys, t_env *e);

void				opencl_render(t_env *e);
void				process_ker_ret(t_env *e, t_cl_param *params, int n);

void				get_prim_map(t_env *e);

void				init_shaders(GLuint vao, GLuint *program, char *vs,
	char *fs);
void				init_texture(GLuint vao, GLuint *tex, int w, int h);
void				init_vao(GLuint *vao);
void				opencl_init(t_env *e);

int					command_line(t_cmd *cmd, int argc, char **argv);

void				init_output(t_ubmp *out, t_argn *argn, t_ubmp *prim_map);
void				direct_output(t_ubmp *out, t_argn *argn, char *path);

void				mouse_click(t_env *e, int key);
void				mouse_callback(GLFWwindow* window, double x, double y);
void				mouse_scroll_callback(GLFWwindow* window, double dx,
	double dy);
void 				mouse_button_callback(GLFWwindow* window, int button,
	int action, int mods);
void				mouse_off(t_env *e, int key);

void				rotate_cam(t_camera *cam, double angle, t_vector axe);
t_vector			cl_float4_to_vector(cl_float4 v);
cl_float4			vector_to_cl_float4(t_vector v);
void				calc_vpul(t_camera *cam);

void				update_kernel_args(t_env *e);

void				parser(t_env *e, const char *src);

int					check_parsed_data(const t_argn *argn, const t_camera *cam);
void				parse_images(t_json_value *root,
								t_textures_holder *textures_holder);
void				parse_camera(t_json_value *c, t_camera *cam);
void				parse_lights(t_json_value *l, t_argn *argn,
	t_light **lights);
void				parse_objects(t_json_value *o, t_env *e);
void				parse_render_options(t_json_value *ro, t_argn *argn,
	t_textures_holder *h);
t_texture			parse_texture(t_json_value *t, t_texture default_return,
								t_textures_holder *textures_holder);
void				*parse_materials(t_json_value *m,
									t_material_holder *materials,
									t_textures_holder *textures_holder);
t_material			parse_material(t_json_value *m, t_material out,
	t_textures_holder *textures_holder);
t_material			default_material(void);

cl_float4			cl_vector_from_json_array(t_json_value *node,
	cl_float4 default_return);

cl_float4			cl_float4_normalize(cl_float4 v);
cl_float4			cl_float4_add(cl_float4 a, cl_float4 b);
void				cl_float4_p_add(cl_float4 *a, cl_float4 b);
cl_float4			cl_float4_scale(cl_float4 v, cl_float s);
cl_float4			cl_float4_sub(cl_float4 a, cl_float4 b);
cl_float4			ft_vector_thales(cl_float4 origin, cl_float4 v1,
						cl_float4 v2, cl_float4 r);

#endif
