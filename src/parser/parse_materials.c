/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_materials.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 02:01:09 by hmartzol          #+#    #+#             */
/*   Updated: 2017/04/18 17:18:45 by pgourran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
/*
inline static t_material	parse_material_0(t_json_value *m, t_material out,
											t_textures_holder *textures_holder)
{
	t_json_value	*v;

	v = ft_json_search_pair_in_object(m,
		(t_json_string){.length = 5, .ptr = "color"});
	out.color = cl_vector_from_json_array(v, out.color);
	v = ft_json_search_pair_in_object(m,
		(t_json_string){.length = 7, .ptr = "diffuse"});
	out.diffuse = cl_vector_from_json_array(v, out.diffuse);
	v = ft_json_search_pair_in_object(m,
		(t_json_string){.length = 8, .ptr = "specular"});
	out.specular = cl_vector_from_json_array(v, out.specular);
	v = ft_json_search_pair_in_object(m,
		(t_json_string){.length = 10, .ptr = "reflection"});
	(v != NULL && v->type == number && v->ptr != NULL) ?
		out.reflection = (cl_float) * (double*)v->ptr : 0;
	v = ft_json_search_pair_in_object(m,
		(t_json_string){.length = 7, .ptr = "texture"});
	out.texture = parse_texture(v, out.texture, textures_holder);
	v = ft_json_search_pair_in_object(m,
		(t_json_string){.length = 10, .ptr = "normal_map"});
	out.normal_map = parse_texture(v, out.normal_map, textures_holder);
	return (out);
}*/

/*
void						sf_parse_texture(void *ptr, void *data)
{
	parse_texture(ptr, (t_texture){0, {{0}}, {{0}}}, data);
}
*/

void						sf_perturbation_color(void *ptr, void *data)
{
	if (!ft_strcmp(ptr, "sine"))
		*(cl_int*)data = SINE;
	else if (!ft_strcmp(ptr, "checkerboard"))
		*(cl_int*)data = CHECKERBOARD;
	else
		*(cl_int*)data = 0;
}

t_material					parse_material(t_json_value *m, t_material *out,
											t_textures_holder *textures_holder)
{
	void	**tmp1;
	void	**tmp2;

	tmp1 = (void*[2]){&out->texture, textures_holder};
	tmp2 = (void*[2]){&out->normal_map, textures_holder};
	ft_json_accesses(m, "ro>d* ro>d* ro>>d* <o>s# ro>v# ro>v# ro>v# ro>N* ro>v# ro>v#",
		"refraction", &out->refraction,
		"brightness", &out->brightness,
		"perturbation",
			"normal", &out->perturbation.normal,
			"color", sf_perturbation_color, &out->perturbation.color,
		"color", clv4, &out->color,
		"diffuse", clv4, &out->diffuse,
		"specular", clv4, &out->specular,
		"reflection", &out->reflection, //
		"texture", parse_texture, tmp1,
		"normal_map", parse_texture, tmp2
			);
	return (*out);
}

/*
t_material					parse_material(t_json_value *m, t_material out,
											t_textures_holder *textures_holder)
{
	t_json_value	*v[2];

	if (!ft_json_test_type(m, object))
		return (out);
	v[0] = ft_json_search_pair_in_object(m,
		(t_json_string){.length = 10, .ptr = "refraction"});
	(v[0] != NULL && v[0]->type == number && v[0]->ptr != NULL) ?
		out.refraction = (cl_float) * (double*)v[0]->ptr : 0;
	v[0] = ft_json_search_pair_in_object(m,
		(t_json_string){.length = 10, .ptr = "brightness"});
	(v[0] != NULL && v[0]->type == number && v[0]->ptr != NULL) ?
		out.brightness = (cl_float) * (double*)v[0]->ptr : 0;
	v[0] = ft_json_search_pair_in_object(m,
		(t_json_string){.length = 12, .ptr = "perturbation"});
	v[1] = ft_json_search_pair_in_object(v[0],
		(t_json_string){.length = 6, .ptr = "normal"});
	(v[1] != NULL && v[1]->type == number && v[1]->ptr != NULL) ?
		out.perturbation.normal = (cl_float) * (double*)v[1]->ptr : 0;
	v[1] = ft_json_search_pair_in_object(v[0],
		(t_json_string){.length = 5, .ptr = "color"});
	out.perturbation.color = ft_json_check_string(v[1], 3,
	(char**)(size_t[3]){(size_t)NULL, (size_t)"sine", (size_t)"checkerboard"},
	out.perturbation.color);
	return (parse_material_0(m, out, textures_holder));
}
*/

inline static char			*new_material(t_json_pair *p, unsigned long i,
										t_material_holder *materials,
										t_textures_holder *textures_holder)
{
	char	*out;

	(void)i;
	(void)materials;
	(void)textures_holder;
	if (p == NULL || p->key == NULL || p->value == NULL || p->key->ptr == NULL
		|| p->key->length == 0 || (out = ft_strdup(p->key->ptr)) == NULL)
		return (NULL);
	parse_material(p->value, &materials->materials[ft_strcmp("default", out) ? i + 1 : 0], textures_holder);
	return (out);
}

/*
void						*parse_materials(t_json_value *m,
											t_material_holder *materials,
											t_textures_holder *textures_holder)
{
	t_json_object	*obj;
	t_pair			*out;
	unsigned long	i;

	out = NULL;
	if (m == NULL || m->type != object || m->ptr == NULL ||
		(obj = (t_json_object*)m->ptr)->nb_pairs == 0 || obj->pair == NULL ||
		(out = (t_pair*)ft_memalloc(sizeof(t_pair) * obj->nb_pairs)) == NULL ||
		(materials->materials =
		ft_memalloc(sizeof(t_material) * (obj->nb_pairs + 1))) == NULL)
		return (out != NULL ? ft_free(out) : NULL);
	if ((materials->name =
			ft_memalloc(sizeof(char*) * (obj->nb_pairs + 1))) == NULL)
	{
		ft_memdel((void**)&materials->materials);
		return (ft_free(out));
	}
	i = -1;
	materials->materials[0] = default_material();
	while (++i < obj->nb_pairs)
		materials->name[i] = new_material(obj->pair[i], i, materials,
										textures_holder);
	materials->nb_materials = obj->nb_pairs + 1;
	return (NULL);
}
*/

void						*parse_materials(t_json_object *obj, t_env *e)
{
//	t_pair			*out;
	unsigned long	i;

	if (obj->nb_pairs == 0)
		return (NULL);
//	out = ft_memalloc(sizeof(t_pair) * obj->nb_pairs);
	e->materials.materials = ft_memalloc(sizeof(t_material) * (obj->nb_pairs + 1));
	e->materials.name = ft_memalloc(sizeof(char*) * (obj->nb_pairs + 1));
	e->materials.materials[0] = default_material();
	i = -1;
	while (++i < obj->nb_pairs)
		e->materials.name[i] = new_material(obj->pair[i], i, &e->materials,
										&e->textures);
	e->materials.nb_materials = obj->nb_pairs + 1;
	return (NULL);
}
