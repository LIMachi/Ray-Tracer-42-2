/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 19:24:09 by hmartzol          #+#    #+#             */
/*   Updated: 2017/04/13 06:17:52 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <stdio.h>

void				parser(t_env *e, const char *src)
{
	t_json_value	*root;
	t_json_value	*v;

	root = ft_json_parse_src(ft_str_clear_commentaries((char*)src));
	parse_images(root, &e->textures);
	v = ft_json_search_pair_in_object(root,
		(t_json_string){.length = 14, .ptr = "render_options"});
	parse_render_options(v, &e->argn, &e->textures);
	v = ft_json_search_pair_in_object(root,
		(t_json_string){.length = 6, .ptr = "camera"});
	parse_camera(v, &e->cam);
	v = ft_json_search_pair_in_object(root,
		(t_json_string){.length = 9, .ptr = "materials"});
	parse_materials(v, &e->materials, &e->textures);
	v = ft_json_search_pair_in_object(root,
		(t_json_string){.length = 7, .ptr = "objects"});
	parse_objects(v, e);
	v = ft_json_search_pair_in_object(root,
		(t_json_string){.length = 6, .ptr = "lights"});
	parse_lights(v, &e->argn, &e->lights);
	if (!check_parsed_data(&e->argn, &e->cam))
		ft_error(EINTERN, "Invalid json values\n");
	ft_json_free(root);
	e->argn.nb_info = e->textures.nb_info;
	e->argn.nb_materials = e->materials.nb_materials;
}
