/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 20:41:41 by hmartzol          #+#    #+#             */
/*   Updated: 2017/05/01 21:20:34 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_PARSER_H
# define RT_PARSER_H

typedef struct			s_ods
{
	int					*out;
	const char			**dictionary;
	int					size;
}						t_ods;

typedef struct			s_oth
{
	t_texture			*out;
	t_textures_holder	*th;
}						t_oth;

typedef struct			s_oe
{
	cl_uint				*out;
	t_env				*e;
}						t_oe;

void					jds(char *str, t_ods *ods);
void					clf(void *ptr, cl_float *data, t_json_value_type type);
void					clv4(t_json_value *v, cl_float4 *vector);
void					clv2(t_json_value *v, cl_float2 *vector);

t_primitive				parse_object(t_json_value *o, t_env *e);
void					load_group(t_json_value *o, t_env *e);
void					parse_images(t_json_value *root,
									t_textures_holder *textures_holder);
void					parse_camera(t_json_value *c, t_camera *cam);
void					parse_lights(t_json_array *ar, t_env *e);
void					parse_objects(t_json_array *ar, t_env *e);
void					parse_render_options(t_json_value *ro, t_env *e);
void					parse_texture(t_json_value *t, t_oth *oth);
void					*parse_materials(t_json_object *obj, t_env *e);
t_material				parse_material(t_json_value *m, t_material *out,
										t_textures_holder *textures_holder);
void					parse_groups(t_json_value *v, t_env *e);
t_material				default_material(void);
t_primitive				null_primitive(void);


cl_float4				cl_vector_from_json_array(t_json_value *node,
												cl_float4 default_return);

#endif
