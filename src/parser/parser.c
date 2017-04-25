/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 19:24:09 by hmartzol          #+#    #+#             */
/*   Updated: 2017/04/14 15:11:14 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <stdio.h>

void				clf(void *ptr, cl_float *data, t_json_value_type type)
{
	if (type == number)
		*data = *(double*)ptr;
	else
		*data = *(int*)ptr;
}

void				clv4(t_json_value *v, cl_float4 *vector)
{
	ft_json_accesses(v, "ra>N#ra>N#ra>N#ra>B*", 0, clf, &vector->x, 1, clf,
					&vector->y, 2, clf, &vector->z, 3, &vector->w);
}

void				clv2(t_json_value *v, cl_float2 *vector)
{
	ft_json_accesses(v, "ra>N#ra>N#", 0, clf, &vector->x, 1, clf, &vector->y);
}

void				parser(t_env *e, const char *src)
{
	t_json_value	*root;
	// unsigned long	i;

	root = ft_json_parse_src(ft_str_clear_commentaries((char*)src));
	parse_images(root, &e->textures);

	ft_json_accesses(root, "ro>v# ro>v# ro># r>a# eo>a#", "render_options",
	parse_render_options, e, "camera", parse_camera, &e->cam, "materials",
	parse_materials, e, "lights", parse_lights, e, "groups", parse_groups, e,
	"objects", parse_objects, e);

//	ft_json_accesses(root, "ro>v#", "render_options", parse_render_options, e);

/*	parse_render_options(ft_json_search_pair_in_object(root,
		ft_json_s_string("render_options")), &e->argn, &e->textures);
	parse_camera(ft_json_search_pair_in_object(root,
		ft_json_s_string("camera")), &e->cam);
	parse_materials(ft_json_search_pair_in_object(root,
		ft_json_s_string("materials")), &e->materials, &e->textures);
*/	// parse_groups(ft_json_search_pair_in_object(root,
	// 	ft_json_s_string("groups")), e);
/*	parse_objects(ft_json_search_pair_in_object(root,
		ft_json_s_string("objects")), e);
	parse_lights(ft_json_search_pair_in_object(root,
		ft_json_s_string("lights")), &e->argn, &e->lights);
	// i = -1;
	// while (++i < e->nb_groups)
	// 	if (e->group_constructor[i].prim != NULL)
	// 		ft_memdel((void**)&e->group_constructor[i].prim);
	ft_json_free(root);
	e->argn.nb_info = e->textures.nb_info;
	e->argn.nb_materials = e->materials.nb_materials;
*/
//	ft_json_search_pair_in_object_c_string(root, "render_options")
	printf("json render_options size: %d %d, light ambient: %f direct: %f\n", e->argn.screen_size.x, e->argn.screen_size.y, e->argn.ambient, e->argn.direct);
	printf("cam: pos: %f %f %f\ndir: %f %f %f\n", e->cam.pos.x, e->cam.pos.y, e->cam.pos.z, e->cam.dir.x, e->cam.dir.y, e->cam.dir.z);
	printf("cam: vp_size: %f %f\ndist: %f\n", e->cam.vp_size.x, e->cam.vp_size.y, e->cam.dist);
	ft_end(0);
}
