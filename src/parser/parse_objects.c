/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 02:02:23 by hmartzol          #+#    #+#             */
/*   Updated: 2017/04/14 15:24:51 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <rt.h>

/*
inline static cl_uint		parse_object_material(t_json_value *o,
	t_material_holder *materials, t_textures_holder *textures)
{
	int	i;

	if (o == NULL || o->ptr == NULL)
		return (0);
	if (o->type == object)
	{
		materials->materials = ft_reallocf(materials->materials,
			sizeof(t_material) * materials->nb_materials,
			sizeof(t_material) * (materials->nb_materials + 1));
		materials->name = ft_reallocf(materials->name,
			sizeof(char *) * materials->nb_materials,
			sizeof(char *) * (materials->nb_materials + 1));
		materials->name[materials->nb_materials] = NULL;
		materials->materials[materials->nb_materials] =
			parse_material(o, default_material(), textures);
		return (materials->nb_materials++);
	}
	else if (o->type == string && ((t_json_string*)o->ptr)->ptr != NULL &&
			(i = -1))
		while (++i < materials->nb_materials)
			if (materials->name[i] != NULL &&
				!ft_strcmp(((t_json_string*)o->ptr)->ptr, materials->name[i]))
				return (i + 1);
	return (0);
}

inline static cl_float4		parse_limit(t_json_value *v, cl_float nc)
{
	t_json_value		**ar;
	cl_float4			out;
	t_json_value_type	*la_norm_le_retour;

	la_norm_le_retour = (t_json_value_type[3])
	{integer | number | null, integer | number | null, integer | number | null};
	if (!ft_json_check_array_types(v, 3, la_norm_le_retour))
		return ((cl_float4){.x = nc, .y = nc, .z = nc, .w = 0.0f});
	ar = ((t_json_array*)v->ptr)->value;
	if (ar[0]->type == null)
		out.x = nc;
	else
		out.x = ar[0]->type == integer ?
		(cl_float)*(int*)ar[0]->ptr : (cl_float)*(double*)ar[0]->ptr;
	if (ar[1]->type == null)
		out.y = nc;
	else
		out.y = ar[1]->type == integer ?
		(cl_float)*(int*)ar[1]->ptr : (cl_float)*(double*)ar[1]->ptr;
	if (ar[2]->type == null)
		out.z = nc;
	else
		out.z = ar[2]->type == integer ?
		(cl_float)*(int*)ar[2]->ptr : (cl_float)*(double*)ar[2]->ptr;
	return ((cl_float4){.x = out.x, .y = out.y, .z = out.z, .w = 0.0f});
}

t_primitive					parse_object(t_json_value *o,
	t_material_holder *materials, t_textures_holder *textures)
{
	t_json_value	*v;
	t_primitive		p;

	if ((p.type = ft_json_check_string(ft_json_search_pair_in_object_c_string(o,
		"type"), 5, (char**)(size_t[5]){(size_t)"sphere", (size_t)"plane",
		(size_t)"cone", (size_t)"cylinder", (size_t)"paraboloid"}, -1)) == -1)
		p.type = INVALID;
	p.material = parse_object_material(ft_json_search_pair_in_object_c_string(o,
		"material"), materials, textures);
	v = ft_json_search_pair_in_object_c_string(o, "radius");
	p.radius = D_RAD;
	if (v != NULL && (v->type & (integer | number)) && v->ptr != NULL)
		p.radius = (v->type == integer) ? *(int*)v->ptr : *(double*)v->ptr;
	p.position = cl_vector_from_json_array(ft_json_search_pair_in_object(o,
		ft_json_s_string("position")), D_POS);
	p.direction = cl_vector_from_json_array(ft_json_search_pair_in_object(o,
		ft_json_s_string("direction")), D_DIR);
	v = ft_json_acces_value(o, NULL, "oo", "limit", "relative");
	p.limit.relative = (v != NULL && v->type == boolean &&
						v->ptr != NULL && *(int*)v->ptr);
	p.limit.high = parse_limit(ft_json_acces_value(o, NULL, "oo", "limit",
		"high"), FLT_MAX);
	p.limit.low = parse_limit(ft_json_acces_value(o, NULL, "oo", "limit",
		"low"), -FLT_MAX);
	return (p);
}
*/
/*
void						parse_objects(t_json_value *o, t_env *e)
{
	t_json_array	*ar;
	unsigned long	i;

	if (o == NULL || o->type != array || (ar = (t_json_array*)o->ptr) == NULL ||
		ar->nb_values == 0 || ar->value == NULL)
		return ;
	e->prim = ft_malloc(sizeof(t_primitive) * 1024);
	e->group = ft_malloc(sizeof(t_group) * 1024);
	e->argn.nb_objects = 0;
	e->nb_groups = 0;
	i = -1;
	while (++i < ar->nb_values)
		if (ft_json_test_type(ar->value[i], object))
		{
			if ((e->prim[e->argn.nb_objects] =
	parse_object(ar->value[i], &e->materials, &e->textures)).type != INVALID)
			 	++e->argn.nb_objects;
			else
				load_group(ar->value[i], e);
		}
}
*/

void						parse_objects(t_json_array *ar, t_env *e)
{
	unsigned long	i;

	e->prim = ft_malloc(sizeof(t_primitive) * 1024);
	e->group = ft_malloc(sizeof(t_group) * 1024);
	e->argn.nb_objects = 0;
	e->nb_groups = 0;
	i = -1;
	while (++i < ar->nb_values)
		if (ft_json_test_type(ar->value[i], object))
		{
/*			if ((e->prim[e->argn.nb_objects] =
	parse_object(ar->value[i], &e->materials, &e->textures)).type != INVALID)
			 	++e->argn.nb_objects;
			else
				load_group(ar->value[i], e);
*/		}
}
