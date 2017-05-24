/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 00:05:50 by hmartzol          #+#    #+#             */
/*   Updated: 2017/05/24 06:20:30 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <rt_incs.h>
# include <rt_types.h>
# include <rt_cl.h>
# include <sys/stat.h>
# include <time.h>
# define OCL_SOURCE_PATH "./scl/raytracer.cl"
# define NONE 0
# define UPD 1
# define D_POS ((cl_float4){.x = 0, .y = 0, .z = 0, .w = 0})
# define D_DIR ((cl_float4){.x = 0, .y = 0, .z = 1, .w = 0})
# define D_RAD 1.0f

#define _BOOLEAN ((char*[2]){"false", "true"})
#define BOOLEAN (const char**)_BOOLEAN

typedef enum			e_prim_type
{
	INVALID = -1, SPHERE = 0, PLANE = 1, CONE = 2, CYLINDER = 3, PARABOLOID = 4
}						t_prim_type;

#define _TYPES ((char*[5]){"sphere", "plane", "cone", "cylinder", "paraboloid"})
#define TYPES (const char**)_TYPES
#define NB_TYPES 5

typedef enum			e_pert_type
{
	SINE = 1, CHECKERBOARD = 2
}						t_pert_type;

#define _PERTURBATIONS ((char*[3]){"none", "sine", "checkerboard"})
#define PERTURBATIONS (const char**)_PERTURBATIONS
#define NB_PERTURBATIONS 3

typedef enum			e_color_filter
{
	SEPIA = 1, GRAYSCALE = 2, CARTOON = 3
}						t_color_filter;

#define _FILTERS ((char*[4]){"none", "sepia", "grayscale", "cartoon"})
#define FILTERS (const char**)_FILTERS
#define NB_FILTERS 4

typedef struct			s_perturbation
{
	cl_float			normal;
	t_pert_type			color;
}						t_perturbation;

typedef struct			s_texture
{
	cl_ulong			info_index;
	cl_float2			stretch;
	cl_float2			offset;
}						t_texture;

typedef struct			s_material
{
	cl_float4			color;
	cl_float4			diffuse;
	cl_float4			specular;
	cl_float			reflection;
	cl_float			refraction;
	cl_float			brightness;
	t_perturbation		perturbation;
	t_texture			texture;
	t_texture			normal_map;
}						t_material;

typedef struct			s_img_info
{
	cl_ulong			index;
	cl_int2				size;
}						t_img_info;

typedef struct			s_pair
{
	char				*name;
	cl_ulong			index;
}						t_pair;

typedef struct			s_material_holder
{
	int					nb_materials;
	char				**name;
	t_material			*materials;
}						t_material_holder;

typedef struct			s_textures_holder
{
	int					nb_info;
	char				**path;
	t_img_info			*info;
	int					total_raw_size;
	cl_int				*raw_bmp;
}						t_textures_holder;

typedef struct			s_camera
{
	cl_float4			pos;
	cl_float4			dir;
	cl_float4			up;
	cl_float4			right;
	cl_float4			vpul;
	cl_float2			vp_size;
	float				speed;
	float				dist;
	t_quaternion		orientation;
	t_vector			origin_dir;
	t_vector			origin_up;
	t_vector			origin_right;
}						t_camera;

typedef struct			s_limit
{
	cl_int				relative;
	cl_float4			high;
	cl_float4			low;
	cl_float4			rotation;
}						t_limit;

typedef struct			s_primitive
{
	t_prim_type			type;
	cl_float4			position;
	cl_float4			direction;
	cl_float4			orientation;
	cl_float			radius;
	cl_uint				material;
	t_limit				limit;
	cl_uint				group_id;
}						t_primitive;

typedef struct			s_light
{
	cl_float4			position;
	cl_float4			color;
}						t_light;

typedef struct			s_argn
{
	cl_int2				screen_size;
	cl_int				nb_objects;
	cl_int				nb_lights;
	cl_int				map_primitives;
	cl_float			ambient;
	cl_float			direct;
	cl_int				antialias;
	cl_int				bounce_depth;
	t_color_filter		filter;
	cl_int				stereoscopy;
	t_texture			skybox;
	cl_int				nb_info;
	cl_int				nb_materials;
	cl_int				moving;
}						t_argn;

typedef struct			s_mouse
{
	int					is_select;
	int					is_select_right;
	double				x;
	double				y;
}						t_mouse;

typedef struct			s_cmd
{
	char				*scene;
	char				*output;
	int					progress_bar_toggle;
	struct stat			status;
}						t_cmd;

typedef struct			s_keys
{
	int					ctrl;
	int					updated;
	int					cursor;
}						t_keys;

struct s_env;

typedef struct			s_key
{
	int					keycode;
	int					pressed;
	void				(*press)(struct s_env *, int);
	void				(*repeat)(struct s_env *, int);
	void				(*release)(struct s_env *, int);
}						t_key;

typedef struct			s_ctx_glfw
{
	GLFWwindow			*win;
	char				*win_name;
	int					fps;
	t_key				*keys;
	int					nkeys;
	t_key				*mkeys;
	int					nmkeys;
	t_cl_ctx			cl_ctx;
	cl_mem				cl_tex;
	GLuint				tex;
	GLuint				program;
	GLuint				vao;
	t_cl_kernel			*render;
	int					focus;
}						t_ctx_glfw;

typedef struct			s_group_constructor
{
	char				*name;
	unsigned			nb_prims;
	t_primitive			*prim;
}						t_group_constructor;

typedef struct			s_group
{
	unsigned			nb_prims;
	int					*prim_ids;
}						t_group;

typedef struct			s_env
{
	t_light				*lights;
	t_primitive			*prim;
	t_material_holder	materials;
	t_textures_holder	textures;
	t_cmd				cmd;
	t_argn				argn;
	t_camera			cam;
	t_ubmp				prim_map;
	t_keys				keys;
	t_mouse				mouse;
	t_point				window;
	t_ctx_glfw			glfw;
	int					need_reboot;
	unsigned			nb_groups;
	t_group				*group;
	unsigned			nb_group_constructors;
	t_group_constructor	*group_constructor;
}						t_env;

typedef void			(*t_key_f)(t_env *, int);

void					die(int err, char *msg, const char *err_log, ...);

void					rt(t_env *e);
void					update(t_env *e);

void					save(t_env *e, int keycode);
t_env					*glfw_env(t_env *e);
GLFWwindow				*glfw_init(t_env *e, char *name, int w, int h);
void					key_callback(GLFWwindow *win, int key, int scan,
									int action);
void					mouse_callback(GLFWwindow *window, double x, double y);
void					file_drop_callback(GLFWwindow *win, int n,
										const char **paths);
void					window_focus(GLFWwindow *win, int focus);
void					set_keys(t_env *e);
void					handle_keys(t_key *keys, t_env *e);
int						key_match(int keycode, int action, t_key *key);

void					opencl_render(t_env *e);
void					process_ker_ret(t_env *e, t_cl_param *params, int n);

void					get_prim_map(t_env *e);

void					init_shaders(GLuint vao, GLuint *program, char *vs,
									char *fs);
void					init_texture(GLuint vao, GLuint *tex, int w, int h);
void					init_vao(GLuint *vao);
void					opencl_init(t_env *e, size_t g[2]);

int						command_line(t_cmd *cmd, int argc, char **argv);

void					init_output(t_ubmp *out, t_argn *argn,
									t_ubmp *prim_map);
void					direct_output(t_ubmp *out, t_argn *argn, char *path);

void					mouse_click(t_env *e, int key);
void					mouse_callback(GLFWwindow *window, double x, double y);
void					mouse_scroll_callback(GLFWwindow *window, double dx,
											double dy);
void					mouse_button_callback(GLFWwindow *window,
											int button, int action, int mods);
void					mouse_off(t_env *e, int key);

void					toggle_cursor(t_env *e, int keycode);
void					rotate_cam(t_camera *cam, double angle, t_vector axe);
void					rotate(t_env *e, double x, double y, double z);
t_vector				cl_float4_to_vector(cl_float4 v);
cl_float4				vector_to_cl_float4(t_vector v);
void					calc_vpul(t_camera *cam);

void					update_kernel_args(t_env *e);

void					parser(t_env *e, const char *src);

cl_float4				cl_float4_normalize(cl_float4 v);
cl_float4				cl_float4_add(cl_float4 a, cl_float4 b);
void					cl_float4_p_add(cl_float4 *a, cl_float4 b);
cl_float4				cl_float4_scale(cl_float4 v, cl_float s);
cl_float4				cl_float4_sub(cl_float4 a, cl_float4 b);
cl_float4				ft_vector_thales(cl_float4 origin, cl_float4 v1,
										cl_float4 v2, cl_float4 r);

void					filter_sepia(t_env *e, int keycode);
void					filter_cartoon(t_env *e, int keycode);
void					filter_gray(t_env *e, int keycode);
void					filter_none(t_env *e, int keycode);
void					increase(t_env *e, int keycode);

void					delete_rt_environement(t_env *e);

void					load_file(t_env *e, const char *path);

void					debug(t_env *e);

#endif
