/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 01:59:11 by hmartzol          #+#    #+#             */
/*   Updated: 2017/04/13 05:36:18 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

/*
inline static void	parse_camera_1(t_camera *cam)
{
	cl_float4	t;

	t = cam->dir;
	cam->origin_dir = ft_vector(t.x, t.y, t.z);
	t = cam->up;
	cam->origin_up = ft_vector(t.x, t.y, t.z);
	t = cam->right;
	cam->origin_right = ft_vector(t.x, t.y, t.z);
}

inline static void	parse_camera_0(t_json_value *vps, t_camera *cam)
{
	t_json_value_type	*j_ai_plus_d_idee_pour_railler_la_norme;

	j_ai_plus_d_idee_pour_railler_la_norme =
		(t_json_value_type[2]){integer | number, integer | number};
	if (ft_json_check_array_types(vps, 2,
			j_ai_plus_d_idee_pour_railler_la_norme))
	{
		cam->vp_size.x = ((t_json_array*)vps->ptr)->value[0]->type == integer
			? (cl_float) * (int*)((t_json_array*)vps->ptr)->value[0]->ptr :
			(cl_float) * (double*)((t_json_array*)vps->ptr)->value[0]->ptr;
		cam->vp_size.y = ((t_json_array*)vps->ptr)->value[1]->type == integer
			? (cl_float) * (int*)((t_json_array*)vps->ptr)->value[1]->ptr :
			(cl_float) * (double*)((t_json_array*)vps->ptr)->value[1]->ptr;
	}
}

void				parse_camera(t_json_value *c, t_camera *cam)
{
	t_json_value		*v;

	v = ft_json_search_pair_in_object(c,
		(t_json_string){.length = 8, .ptr = "position"});
	cam->pos = cl_vector_from_json_array(v, cam->pos);
	v = ft_json_search_pair_in_object(c,
		(t_json_string){.length = 9, .ptr = "direction"});
	cam->dir = cl_vector_from_json_array(v, cam->dir);
	v = ft_json_search_pair_in_object(c,
		(t_json_string){.length = 2, .ptr = "up"});
	cam->up = cl_vector_from_json_array(v, cam->up);
	v = ft_json_search_pair_in_object(c,
		(t_json_string){.length = 5, .ptr = "right"});
	cam->right = cl_vector_from_json_array(v, cam->right);
	v = ft_json_search_pair_in_object(c,
		(t_json_string){.length = 7, .ptr = "vp_size"});
	parse_camera_0(v, cam);
	v = ft_json_search_pair_in_object(c,
		(t_json_string){.length = 4, .ptr = "dist"});
	if (v != NULL && (v->type == number || v->type == integer) &&
			v->ptr != NULL)
		cam->dist = (v->type == number) ?
			(cl_float) * (double*)v->ptr : (cl_float) * (int*)v->ptr;
	parse_camera_1(cam);
}
*/

/*
void				vp_size(void *ptr, void *data)
{
	cl_float4		*vector;

	vector = (cl_float4*)data;
	ft_json_accesses(ptr, "ra>N#ra>N#", 0, clf, &vector->x, 1, clf, &vector->y);
}
*/

void				parse_camera(t_json_value *c, t_camera *cam)
{
	ft_json_accesses(c, "ro>v#ro>v#ro>v#ro>v#ro>v#ro>N#",
		"position", clv4, &cam->pos,
		"direction", clv4, &cam->dir,
		"up", clv4, &cam->up,
		"right", clv4, &cam->right,
		"vp_size", clv2, &cam->vp_size,
		"dist", clf, &cam->dist);
	cam->origin_dir = (t_vector){.x = cam->dir.x, .y = cam->dir.y,
								.z = cam->dir.z};
	cam->origin_up = (t_vector){.x = cam->up.x, .y = cam->up.y,
								.z = cam->up.z};
	cam->origin_right = (t_vector){.x = cam->right.x, .y = cam->right.y,
								.z = cam->right.z};
}
