// raytracer kernel is pretty cool actually

#if __OPENCL_VERSION__ < 120
# define COS cosf
#else
# define COS cos
#endif

#define NONE 0
#define NO_PRIMITIVE -1

typedef enum		e_prim_type
{
	SPHERE = 0, PLANE = 1, CONE = 2, CYLINDER = 3, PARABOLOID = 4
}					t_prim_type;

typedef enum		e_pert_type
{
	SINE = 1, CHECKERBOARD = 2
}					t_pert_type;

typedef enum		e_color_filter
{
	SEPIA = 1, GRAYSCALE = 2, CARTOON = 3
}					t_color_filter;

typedef enum		e_ray_type
{
	ORIGIN = 0, REFLECTED = 1, REFRACTED = 2
}					t_ray_type;

typedef struct		s_perturbation
{
	float			normal;
	t_pert_type		color;
}					t_perturbation;

typedef struct		s_texture
{
	ulong			info_index;
	float2			stretch;
	float2			offset;
}					t_texture;

typedef struct		s_material
{
	float4			color;
	float4			diffuse;
	float4			specular;
	float			reflection;
	float			refraction;
	float			brightness;
	t_perturbation	perturbation;
	t_texture		texture;
	t_texture		normal_map;
}					t_material;

typedef struct		s_img_info
{
	ulong			index;
	int2			size;
}					t_img_info;

typedef struct		s_camera
{
	float4			pos;
	float4			dir;
	float4			up;
	float4			right;
	float4			vpul;
	float2			vp_size;
}					t_camera;

typedef struct		s_limit
{
	int				relative;
	float4			high;
	float4			low;
}					t_limit;

typedef struct		s_primitive
{
	t_prim_type		type;
	float4			position;
	float4			direction;
	float			radius;
	uint			material;
	t_limit			limit;
}					t_primitive;

typedef struct		s_light
{
	float4			position;
	float4			color;
}					t_light;

typedef struct		s_argn
{
	int2			screen_size;
	int				nb_objects;
	int				nb_lights;
	int				map_primitives;
	float			ambient;
	float			direct;
	int				antialias;
	int				bounce_depth;
	int				filter;
	int				stereoscopy;
	t_texture		skybox;
	int				nb_info;
	int				nb_materials;
}					t_argn;

typedef struct		s_ray
{
	float4			origin;
	float4			direction;
	float			dist;
	float			weight;
	int				depth;
	int				primitive_id;
	t_ray_type		type;
	float4			color;
	int				node;
}					t_ray;

//j'aime les commentaires, et vous? :p
/*
   NOTE HYPER IMPORTANTE:
   pour la compatibilité AMD, il faut continuer d'utiliser les flags __global et les pointeurs
   (AMD ne copie pas les déréférencements de pointeurs dans la stack, ce qui fait que les objets et la lumière n'étaient pas envoyé aux calculs)
   */

int		plane_intersect(__global t_primitive *obj, t_ray *ray, float *dist);
int		sphere_intersect(__global t_primitive *obj, t_ray *ray, float *dist);
int		cylinder_intersect(__global t_primitive *obj, t_ray *ray, float *dist);
int		cone_intersect(__global t_primitive *obj, t_ray *ray, float *dist);
int		paraboloid_intersect(__global t_primitive *obj, t_ray *ray, float *dist);
int		intersect(__global t_primitive *obj, t_ray *ray, float *dist);
int		solve_quadratic(float a, float b, float c, float *dist);
float4	get_normal(__global t_primitive *obj, __global t_material *mat, t_ray *ray, float4 point, __global int *raw_bmp, __global t_img_info *img_info);
float4	input_ray(float4 dir, float4 norm);
float4	color_texture(__global t_primitive *prim, __global t_texture *tex, float4 normal, __global t_img_info *info, __global int *raw_bmp, float4 col);
float4	skybox(__global t_texture *tex, t_ray ray, __global int *raw_bmp, __global t_img_info *img_info);
int		color_to_int(float4 color);
float4	int_to_color(int c);
int		raytrace(t_ray *ray, __global t_argn *argn, __global t_primitive *objects, __global t_light *lights, int *result, int *l_id);

int		quadratic(float a, float b, float c, float2 *ret);

#if 0
# define DOT local_dot
# define NORMALIZE local_normalize
# define LENGTH local_length
# define CROSS local_cross

inline float4	local_normalize(float4 v);
inline float	local_dot(float4 v1, float4 v2);
inline float4	local_cross(float4 v1, float4 v2);
inline float	local_length(float4 v);

inline float4	local_cross(float4 v1, float4 v2)
{
	float4 res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

inline float	local_dot(float4 v1, float4 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

inline float4	local_normalize(float4 v)
{
	float	t;

	if ((v.x == 0.0f && v.y == 0.0f && v.z == 0.0f) || (t = (v.x * v.x + v.y * v.y + v.z * v.z)) == 1.0f)
		return (v);
	return (v / sqrt(t));
}

inline float	local_length(float4 v)
{
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
#else
# define DOT dot
# define NORMALIZE normalize
# define LENGTH length
# define CROSS cross
#endif

// error correction
#ifndef EPSILON
# define EPSILON 0.0001f
#endif

// for shadows we need a larger value
#ifndef SHADOW_E
# define SHADOW_E 0.1f
#endif

// maximum ray count
#ifndef MAX_RAY_COUNT
# define MAX_RAY_COUNT (1 << 8)
#endif

// minimum direct lighting coefficient
#ifndef MIN_DIRECT
# define MIN_DIRECT 0.95f
#endif

// normal perturbation size
#ifndef NORMAL_PERTURBATION_SIZE
# define NORMAL_PERTURBATION_SIZE 10.0f
#endif

// color perturbation checkerboard size
#ifndef CHECKER_SIZE
# define CHECKER_SIZE 10
#endif

// cartoon effect steps
#ifndef CARTOON_STEPS
# define CARTOON_STEPS 3
#endif

int				quadratic(float a, float b, float c, float2 *ret)
{
	float	delta;

	delta = b * b - (4.0f * a * c);
	if (delta <= 0)
		return (0);
	ret->x = (b - sqrt(delta)) / (2.0f * a);
	ret->y = (b + sqrt(delta)) / (2.0f * a);
	return (1);
}

int		plane_intersect(__global t_primitive *obj, t_ray *ray, float *dist)
{
	float d = DOT(obj->direction, ray->direction);

	// facing the plane (d == 0)
	if (d > -0.01f && d < 0.01f)
		return (0);

	float new_dist = DOT(obj->position + EPSILON - ray->origin, obj->direction) / d;

	if (new_dist > EPSILON && (new_dist < *dist || *dist < 0.01f))
	{
		*dist = new_dist;
		return (d > 0 ? -1 : 1);
	}
	return (0);
}
/*
int				rt_plan(__global t_obj *o, t_ray *ray)
{
	float	d = dot(o->dir, ray->dir);
	float	t;

	// ray paralele au plan
	if (d > -0.01f && d < 0.01f)
		return (0);
	t = dot(o->pos + EPSILON - ray->ori, o->dir) / d;
	if (t > EPSILON && (t < ray->t || ray->t < 0.01f))
	{
		ray->t = t;
		return (d > 0 ? -1 : 1);
	}
	return (0);
}
*/
int		sphere_intersect(__global t_primitive *obj, t_ray *ray, float *dist)
{
	float4 pos = obj->position - ray->origin;
	float2 t;
	float a = DOT(ray->direction, ray->direction);
	float b = 2.0f * DOT(ray->direction, pos);
	float c = DOT(pos, pos) - obj->radius * obj->radius;
	if(quadratic(a, b, c, &t))
	{
		if (t.x < t.y && t.x > 0.01 && (t.x < *dist || *dist <= 0.01))
		{
			if (t.x < 0.01)
				*dist = 0.01;
			else
				*dist = t.x;
			return (1);
		}
		else if (t.y > 0.01 && (t.y < *dist || *dist <= 0.01))
		{
			if (t.y < 0.01)
				*dist = 0.01;
			else
				*dist = t.y;
			return (-1);
		}
	}
	return (0);

//	return solve_quadratic(a, b, c, dist);
}

int		cylinder_intersect(__global t_primitive *obj, t_ray *ray, float *dist)
{
	float4 pos = obj->position - ray->origin;
	float4 p = CROSS(pos, obj->direction);
	float4 r = CROSS(ray->direction, obj->direction);

	float2 t;
	float a = DOT(r, r);
	float b = 2 * DOT(r, p);
	float c = DOT(p, p) - obj->radius * obj->radius * DOT(obj->direction, obj->direction);
	if(quadratic(a, b, c , &t))
	{
		if (t.x < t.y && t.x > 0.01 && (t.x < *dist || *dist <= 0.01))
		{
			if (t.x < 0.01)
				*dist = 0.01;
			else
				*dist = t.x;
			return (1);
		}
		else if (t.y > 0.01 && (t.y < *dist || *dist <= 0.01))
		{
			if (t.y < 0.01)
				*dist = 0.01;
			else
				*dist = t.y;
			return (-1);
		}
	}
	return (0);
//	return solve_quadratic(a, b, c, dist);
}

int		cone_intersect(__global t_primitive *obj, t_ray *ray, float *dist)
{
	float4 pos = ray->origin - obj->position;
	float4 dir = -ray->direction;
	float2 t;
	float tr = tan(obj->radius * M_PI / 180.0f);
	float r = 1.0f + tr * tr;
	float dd = DOT(dir, obj->direction);
	float xv = DOT(pos, obj->direction);

	float a = DOT(dir, dir) - (r * dd * dd);
	float b = 2.0f * (DOT(dir, pos) - (r * dd * xv));
	float c = DOT(pos, pos) - (r * xv * xv);
	if(quadratic(a, b, c , &t))
	{
		if (t.x < t.y && t.x > 0.01 && (t.x < *dist || *dist <= 0.01))
		{
//			if (t.x < 0.01)
//				*dist = 0.01;
//			else
				*dist = t.x;
			return (1);
		}
		else if (t.y > 0.01 && (t.y < *dist || *dist <= 0.01))
		{
//			if (t.y < 0.01)
//				*dist = 0.01;
//			else
				*dist = t.y;
			return (-1);
		}
	}
	return (0);

//	return solve_quadratic(a, b, c, dist);
}

int		paraboloid_intersect(__global t_primitive *obj, t_ray *ray, float *dist)
{
	float4 pos = ray->origin - obj->position;
	float4 dir = -ray->direction;

	float dv = DOT(dir, obj->direction);
	float xv = DOT(pos, obj->direction);

	float a = DOT(dir, dir) - dv * dv;
	float b = 2.0f * (DOT(dir, pos) - dv * (xv + 2.0f * obj->radius));
	float c = DOT(pos, pos) - xv * (xv + 4.0f * obj->radius);

	return solve_quadratic(a, b, c, dist);
}

int		solve_quadratic(float a, float b, float c, float *dist)
{
	float delta = b * b - 4.0f * a * c;
	if (delta < 0)
		return (0);

	delta = sqrt(delta);
	float x1 = (b - delta) / (2.0f * a);
	float x2 = (b + delta) / (2.0f * a);

	if (x1 < EPSILON) // use x2 if x1 is negative
	{
		if (x2 < EPSILON) // both are negative
			return (0);
		else if (x2 < *dist) // x2 positive
		{
			*dist = x2;
			return (-1);
		}
	}
	else if (x1 < *dist) // x1 positive
	{
		*dist = x1;
		return (1);
	}
	return (0);
}

inline int		limit(__global t_primitive *obj, float4 point)
{
	if (obj->limit.relative)
		point -= obj->position;
	//high
	return (point.x > obj->limit.high.x ||
		point.y > obj->limit.high.y ||
		point.z > obj->limit.high.z ||
		point.x < obj->limit.low.x ||
		point.y < obj->limit.low.y ||
		point.z < obj->limit.low.z);
}

inline int		intersect(__global t_primitive *obj, t_ray *ray, float *dist)
{
	int i = 0;
	float4 raytmp = ray->origin;
	float d = *dist;
	switch (obj->type)
	{
		case SPHERE:
			i = sphere_intersect(obj, ray, dist);
			break;
		case PLANE:
			i = plane_intersect(obj, ray, dist);
			break;
		case CONE:
			i = cone_intersect(obj, ray, dist);
			break;
		case CYLINDER:
			i = cylinder_intersect(obj, ray, dist);
			break;
		case PARABOLOID:
			i = paraboloid_intersect(obj, ray, dist);
			break;
	}
	float4 point = ray->direction * *dist + ray->origin;
		if(limit(obj, point) && obj->type != CONE)
		{
			ray->origin = point;
			switch (obj->type)
			{
				case SPHERE:
					i = sphere_intersect(obj, ray, dist);
					break;
				case PLANE:
					i = plane_intersect(obj, ray, dist);
					break;
				case CONE:
					i = cone_intersect(obj, ray, dist);
					break;
				case CYLINDER:
					i = cylinder_intersect(obj, ray, dist);
					break;
				case PARABOLOID:
					i = paraboloid_intersect(obj, ray, dist);
					break;
			}
			point += ray->direction * *dist;
			if(!limit(obj, point) && *dist < d)
			{
				ray->origin = raytmp;
				point -= ray->origin;
//				*dist = d;
				return(i);
			}
			else
			{
				ray->origin = raytmp;
				*dist = d;
				return(0);
			}
	}
//		else
//			return(0);
	return (i);
}

inline float4	get_normal(__global t_primitive *obj,
							__global t_material *mat,
							t_ray *ray,
							float4 point,
							__global int *raw_bmp,
							__global t_img_info *img_info)
{
	float4 n = (float4)(0, 0, 0, 0);
	float r;

	switch (obj->type)
	{
		case SPHERE:
			n = point - obj->position;
			break;
		case PLANE:
			n = obj->direction;
			break;
		case CYLINDER:
			n = DOT(obj->direction, obj->position - point) * obj->direction + (point - obj->position);
			break;
		case CONE:
			r = DOT(ray->direction, obj->direction) * ray->dist + DOT(ray->origin - obj->position, obj->direction);
			n = point - obj->position - (1.0f + pow((float)tan(obj->radius * M_PI / 180.0f), 2)) * obj->direction * r;
			// n = ray->origin - obj->position;
			// r = cos(obj->radius * M_PI / 180.0);
			// r = r * r;
			// n = n - obj->direction * dot(n, obj->direction) / r;
			break;
		case PARABOLOID:
			n = point - obj->position - obj->direction * obj->radius;
			break;
		default:
			return (n);
	}
	
//	printf("%f ", mat->perturbation.normal);
	if (mat->perturbation.normal > EPSILON && mat->normal_map.info_index == ULONG_MAX)
	{
		float len = LENGTH(n);
		n.y += COS(ray->origin.y / NORMAL_PERTURBATION_SIZE) * mat->perturbation.normal * (len / NORMAL_PERTURBATION_SIZE);
//		n.y = 10 * sin(n.y);
	}
//	float4	nm = n;
//	if (mat->normal_map.info_index != ULONG_MAX)
//	{
//		__global t_img_info *info = &img_info[mat->normal_map.info_index];
//		nm = color_texture(obj, &mat->normal_map, nm, info, raw_bmp, n);
//		n.x += nm.x * 2.0 - 1.0;
//		n.y += nm.y * 2.0 - 1.0;
//		nm.z = nm.z < 0.5 ? nm.z = 0.5 : 0;
//		n.z -= (nm.z - 0.5) * 2.0;
//	}
	return (NORMALIZE(n));
}

inline float2	texture_map(__global t_primitive *prim, float4 normal)
{
	float2 pos = (float2)(0, 0);

	switch (prim->type)
	{
		case SPHERE:
			pos.x = 0.5f + atan2(normal.z, normal.x) / (2.0f * M_PI);
			pos.y = 0.5f + asinpi(normal.y);
			break;
		default:
			return (float2)(-1);
	}
	return (pos);
}

inline float4	color_texture(__global t_primitive *prim, __global t_texture *tex, float4 normal, __global t_img_info *info, __global int *raw_bmp, float4 col)
{
	float2 pos = texture_map(prim, normal);
	if (pos.x == -1)
		return (col);
	if (tex->stretch.x != 0.0f && tex->stretch.y != 0.0f)
		pos /= tex->stretch;
	pos += tex->offset;
	pos = fmod(pos, 1.0f);

	int x = pos.x * info->size.x;
	int y = pos.y * info->size.y;
	int raw_c = raw_bmp[info->index + y * (int)info->size.x + x] & 0x00FFFFFF;
	return int_to_color(raw_c);
}

inline float4	color_perturbation(float4 color, __global t_primitive *prim,
		t_pert_type pert, float4 normal)
{
	float2 pos = texture_map(prim, normal);

	switch (pert)
	{
		case CHECKERBOARD:
			if (fmod(pos.x * CHECKER_SIZE, 2) <= 1.0f ^ fmod(pos.y *
					CHECKER_SIZE, 2) <= 1.0f)
				color /= 1.5f;
			break;
		case SINE:
			color *= clamp(fabs(cos((pos.x + pos.y) * 10 * CHECKER_SIZE)), 0.5f, 1.0f);
			break;
	}

	return (color);
}

inline int		color_to_int(float4 color)
{
	color = clamp(color * 255.0f, 0.0f, 255.0f);
	return (int)(((int)color.x << 16) + ((int)color.y << 8) + (int)color.z);
}

inline float4	int_to_color(int c)
{
	float b = (c & 0xFF) / 255.0f;
	float g = ((c & 0xFF00) >> 8) / 255.0f;
	float r = ((c & 0xFF0000) >> 16) / 255.0f;
	return (float4)(r, g, b, 0.0f);
}

inline float4		color_filter(float4 color, t_color_filter filter)
{
	float4	out;
	float	t;

	switch (filter)
	{
		case SEPIA:
			out.x = color.x * 0.393f + color.y * 0.769f + color.z * 0.189f;
			out.y = color.x * 0.349f + color.y * 0.686f + color.z * 0.168f;
			out.z = color.x * 0.272f + color.y * 0.534f + color.z * 0.131f;
			break;
		case GRAYSCALE:
			t = (color.x + color.y + color.z) / 3.0f;
			out.x = t;
			out.y = t;
			out.z = t;
			break;
		case CARTOON:
			out.x = floor(color.x * CARTOON_STEPS) / CARTOON_STEPS;
			out.y = floor(color.y * CARTOON_STEPS) / CARTOON_STEPS;
			out.z = floor(color.z * CARTOON_STEPS) / CARTOON_STEPS;
			break;
		default:
			out = color;
			break;
	}

	return (out);
}

float4		get_light_color(t_ray *ray, __global t_light *lights, __global t_argn *argn, int *l_id)
{
	float4	c = (float4)0;
	t_ray	ray_l;
	float	dist_l;
	float	scal;
	float	dist;

	dist = ray->dist;
	for (int cur_l = 0; cur_l < argn->nb_lights; cur_l++)
	{
		t_light light = lights[cur_l];
		
		if (argn->direct > EPSILON && light.position.w < 0.99)
		{
			ray_l.direction = light.position - ray->origin;
			dist_l = LENGTH(ray_l.direction);
			ray_l.direction /= dist_l;
			ray_l.origin = ray->origin;
			if (dist_l > EPSILON && dist_l < dist)
			{
				scal = DOT(ray_l.direction, ray->direction);
				if (scal > MIN_DIRECT)
				{
					c += (light.color * (scal - MIN_DIRECT) / (1.0f - MIN_DIRECT));
					*l_id = cur_l;
					dist = dist_l;
				}
			}
		}
	}
	if (*l_id > -1)
		*l_id = -*l_id - 2;
	return (c);
}

int		raytrace(t_ray *ray, __global t_argn *argn, __global t_primitive *objects, __global t_light *lights, int *result, int *id_l)
{
	int id = NO_PRIMITIVE;
	int cur;
	int temp;

	*result = 0;
	for (cur = 0; cur < argn->nb_objects; cur++)
	{
		if ((temp = intersect(&objects[cur], ray, &ray->dist)))
		{
			id = cur;
			*result = temp;
		}
	}
	ray->color = get_light_color(ray, lights, argn, id_l);
	if (*id_l == -1)
		*id_l = id;
	return (id);
}

inline float4	input_ray(float4 dir, float4 norm)
{
	return (2 * DOT(-dir, norm) * norm - dir);
}


float4		get_color(t_ray *ray,  float4 normal, __global t_material *mat, __global t_primitive *obj, __global t_primitive *objects,
	__global int *raw_bmp, __global t_img_info *img_info, __global t_light *lights, __global t_argn *argn, float4 p)
{
	float4	c = (float4)0;
	int shadow = 0;
	t_ray	ray_l;
	float dist = MAXFLOAT;
	
	for (int l_cur = 0; l_cur < argn->nb_lights; l_cur++)
	{
		float	dist_l;
		t_light	light = lights[l_cur];
		if(light.position.w < 0.9)
		{
			ray_l.direction = light.position - p;
			dist_l = LENGTH(ray_l.direction);
		}
		else
		{
			ray_l.direction = light.position;
			dist_l = MAXFLOAT;
		}
		ray_l.direction = NORMALIZE(ray_l.direction);
		ray_l.origin = p + SHADOW_E * ray_l.direction;
		shadow = 0;
		for (int cur = 0; cur < argn->nb_objects; cur++)
		{
			if ((shadow = intersect(&objects[cur], &ray_l, &dist)) != 0)
			{
				if (dist > EPSILON && dist < dist_l)
					break ;
//				else
//					shadow = 0;
			}
		}
		float4 col = mat->color;
		
		if (mat->texture.info_index != ULONG_MAX)
		{
			__global t_img_info *info = &img_info[mat->texture.info_index];
			col = color_texture(obj, &mat->texture, normal, info, raw_bmp, col);
//			c += col;
		}
		else
			c += light.color * col * argn->ambient;
		if (shadow)
			continue ;
		float scale;
		if ((scale = DOT(ray_l.direction, normal)) > 0 && mat->texture.info_index == ULONG_MAX)
			c += light.color * mat->diffuse * scale;
		else if (scale > 0)
			c += light.color * col * scale;
//		float4 ir = NORMALIZE(2 * scale * normal - ray_l.direction);
		float4 ir = (ray_l.direction - ray->direction) / 2;
		if ((scale = DOT(ir, normal)))
			c += light.color * mat->specular * pow(scale, mat->brightness) > 0 ? c : 0;
	}
	c = clamp(c / (float)argn->nb_lights, 0.0f, 1.0f);
	c = color_perturbation(c, obj, mat->perturbation.color, normal);
	return (c);
}

float4	skybox(__global t_texture *tex, t_ray ray, __global int *raw_bmp, __global t_img_info *img_info)
{
	if (tex->info_index == ULONG_MAX)
		return (float4)(0, 0, 0, 0);

	float4 normal = NORMALIZE(ray.direction);

	float2 pos;
	pos.x = 0.5f + atan2(normal.z, normal.x) / (2.0f * M_PI);
	pos.y = 0.5f + asinpi(normal.y);

	t_img_info info = img_info[tex->info_index];
	int x = clamp((int)(pos.x * info.size.x), 0, info.size.x - 1);
	int y = clamp((int)(pos.y * info.size.y), 0, info.size.y - 1);
	int raw_c = raw_bmp[info.index + y * info.size.x + x] & 0x00FFFFFF;
	return int_to_color(raw_c);
}

// our stack operations
#define PUSH_RAY(q, r, c) q[c++] = r;

__kernel void	rt_kernel(
		__write_only image2d_t	out,
		__global int			*prim_map,
		__global t_argn			*argn,
		__global t_primitive	*objects,
		__global t_light		*lights,
		__global t_camera		*cam,
		__global t_img_info		*img_info,
		__global t_material		*materials,
		__global int			*raw_bmp)
{
	size_t i = get_global_id(0);
	size_t j = get_global_id(1);
	size_t l = get_global_size(0);

	if (i >= (size_t)argn->screen_size.x * (size_t)argn->screen_size.y)
		return ;

	float x = (float)i;
	float y = (float)j;
	t_ray 		*cur_ray;
	t_ray		queue[MAX_RAY_COUNT];
	int			queue_end = 0;

	int aa_x;
	int aa_y;
	int count = 0;

	float4 color = (float4)(0, 0, 0, 0);

	for (aa_y = 0; aa_y < argn->antialias; aa_y++)
	{
		for (aa_x = 0; aa_x < argn->antialias; aa_x++)
		{
			float2 aa;
			for (int i = 0; i < MAX_RAY_COUNT; i++) {
				queue[i].weight = 0;
			}
			aa.x = x + (aa_x - argn->antialias / 2.0f) / argn->antialias;
			aa.y = y + (aa_y - argn->antialias / 2.0f) / argn->antialias;
			t_ray ray;
			ray.direction = NORMALIZE(cam->vpul + NORMALIZE(cam->right) * (aa.x) - NORMALIZE(cam->up) * (aa.y));
			ray.origin = cam->pos;
			ray.dist = MAXFLOAT;
			ray.type = ORIGIN;
			ray.depth = 0;
			ray.weight = 1.0f;
			ray.color = color;
			ray.node = -1;
			int cur_ray_id = 0;
			count++;
			PUSH_RAY(queue, ray, queue_end);
			while ((cur_ray = &queue[cur_ray_id])->weight > EPSILON)
			{
				cur_ray_id++;
				int result = 0;
				int l_id = -1;
				int cur_id = raytrace(cur_ray, argn, objects, lights, &result, &l_id);
				if (cur_ray->depth == 0)
					prim_map[i + l * j] = l_id + 1;
				if (!result)
				{
					cur_ray->color += skybox(&argn->skybox, *cur_ray, raw_bmp, img_info);
					continue;
				}
				float4 p = cur_ray->origin + cur_ray->dist * cur_ray->direction;
				__global t_material *mat = &materials[objects[cur_id].material];
				float4 normal = get_normal(&objects[cur_id], mat, cur_ray, p, raw_bmp, img_info);
				__global t_img_info *inf = &img_info[mat->normal_map.info_index];
				float4 nm = color_texture(objects, &mat->normal_map, normal, inf, raw_bmp, (float4)(0,0,0,0));
				normal.x += nm.x * 2 - 1;
				normal.y -= nm.y * 2 - 1;
				if(nm.z < 0.5)
					nm.z = 0.5;
				normal.z -= (nm.z - 0.5) * 2;
				cur_ray->color += get_color(cur_ray, normal, mat, objects + cur_id, objects, raw_bmp, img_info, lights, argn, p);
				cur_ray->origin = p;
				if (cur_ray->depth >= argn->bounce_depth)
					continue;
				float lum = mat->reflection;
				float c0i = DOT(normal, -cur_ray->direction);
				float sc = 1 - c0i;
				float r0 = sc;
				t_ray r_ray;
				sc *= sc;
				sc *= sc;
				sc *= r0;
				r0 = (1 - mat->refraction) / (1 + mat->refraction);
				r0 *= r0;
				r0 = (1 - r0) * sc + r0;
				r_ray.dist = MAXFLOAT;
				r_ray.color = (float4)(0);
				r_ray.node = cur_ray_id - 1;
				if (r0 > EPSILON)
				{
					float4 reflect = NORMALIZE(cur_ray->direction - 2.0f * DOT(cur_ray->direction, normal) * normal);
					r_ray.direction = reflect;
					r_ray.origin = cur_ray->origin + EPSILON * r_ray.direction;
					r_ray.depth = cur_ray->depth + 1;
					r_ray.weight = r0 * lum * cur_ray->weight;
					r_ray.type = REFLECTED;
					if (r_ray.weight > EPSILON)
						PUSH_RAY(queue, r_ray, queue_end);
				}
				if ((1 - r0) > EPSILON)
				{
					float	eta = result > 0 ? 1.0 / mat->refraction : mat->refraction;
					float	e2 = eta * eta;
					e2 = 1 - e2 * (1 - c0i * c0i);
					if (e2 < 0)
						continue ;
					e2 = eta * c0i - sqrt(e2);
					float4	refracted = NORMALIZE(eta * cur_ray->direction + e2 * normal);
					r_ray.dist = MAXFLOAT;
					r_ray.direction = refracted;
					r_ray.origin = cur_ray->origin + EPSILON * r_ray.direction;
					r_ray.depth = cur_ray->depth + 1;
					r_ray.weight = (1 - r0) * lum * cur_ray->weight;
					r_ray.type = REFRACTED;
					if (r_ray.weight > EPSILON)
						PUSH_RAY(queue, r_ray, queue_end);
				}
			}
		}
	}
	color = clamp(queue[0].color, 0.0f, 1.0f);
	color /= count;
	if (argn->filter != NONE)
		color = color_filter(color, argn->filter);
	write_imagef(out, (int2)(i, j), (float4)(color.xyz, 1.0));
}
