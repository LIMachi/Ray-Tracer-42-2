/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_images.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 17:10:35 by hmartzol          #+#    #+#             */
/*   Updated: 2017/04/14 08:30:07 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <stdio.h>

inline static int	add_texture(t_textures_holder *textures_holder)
{
	t_ubmp			*ubmp;

	if ((ubmp = ft_bmp_to_ubmp(ft_bitmap_file_load(
		textures_holder->path[textures_holder->nb_info]))) == NULL)
		return (ft_error(EINTERN, "bitmap could not be found/opened\n"));
	textures_holder->info[textures_holder->nb_info].size =
		(cl_int2){.x = ubmp->size.x, .y = ubmp->size.y};
	if (textures_holder->nb_info)
		textures_holder->info[textures_holder->nb_info].index =
		textures_holder->info[textures_holder->nb_info - 1].index +
		textures_holder->info[textures_holder->nb_info - 1].size.x *
		textures_holder->info[textures_holder->nb_info - 1].size.y;
	else
		textures_holder->info[textures_holder->nb_info].index = 0;
	textures_holder->total_raw_size =
		textures_holder->info[textures_holder->nb_info].index +
		ubmp->size.x * ubmp->size.y;
	textures_holder->raw_bmp = ft_reallocf(textures_holder->raw_bmp,
		textures_holder->info[textures_holder->nb_info].index * sizeof(int),
		textures_holder->total_raw_size * sizeof(int));
	ft_memmove(&textures_holder->raw_bmp[textures_holder->info[
		textures_holder->nb_info].index], ubmp->data,
		ubmp->size.x * ubmp->size.y * sizeof(int));
	ft_free(ubmp->data);
	return ((int)(size_t)ft_free(ubmp));
}

/*
inline static void	parse_image(t_json_value *sp, t_textures_holder *textures_holder)
{
	t_json_string	*str;
	char			buff[PATH_MAX];
	int				i;

	if (sp == NULL || sp->type != string || sp->ptr == NULL)
		return ;
	str = (t_json_string*)sp->ptr;
	ft_realpath(str->ptr, buff);
	i = -1;
	while (++i < textures_holder->nb_info)
		if (!ft_strcmp(buff, textures_holder->path[i]))
			break ;
	if (i == textures_holder->nb_info)
	{
		textures_holder->path = ft_reallocf(textures_holder->path,
			sizeof(char**) * textures_holder->nb_info,
			sizeof(char**) * (textures_holder->nb_info + 1));
		textures_holder->info = ft_reallocf(textures_holder->info,
			sizeof(t_img_info) * textures_holder->nb_info,
			sizeof(t_img_info) * (textures_holder->nb_info + 1));
		textures_holder->path[textures_holder->nb_info] = ft_strdup(buff);
		(void)add_texture(textures_holder);
		++textures_holder->nb_info;
	}
}
*/

inline static void	parse_image(char *str, t_textures_holder *textures_holder)
{
	char			buff[PATH_MAX];
	int				i;

	ft_realpath(str, buff);
	i = 0;
	while (i < textures_holder->nb_info &&
			ft_strcmp(buff, textures_holder->path[i]))
		++i;
	if (i != textures_holder->nb_info)
		return ;
	textures_holder->path = ft_reallocf(textures_holder->path,
		sizeof(char**) * textures_holder->nb_info,
		sizeof(char**) * (textures_holder->nb_info + 1));
	textures_holder->info = ft_reallocf(textures_holder->info,
		sizeof(t_img_info) * textures_holder->nb_info,
		sizeof(t_img_info) * (textures_holder->nb_info + 1));
	textures_holder->path[textures_holder->nb_info] = ft_strdup(buff);
	(void)add_texture(textures_holder);
	++textures_holder->nb_info;
}

/*
inline static void	parse_primitive_group_images(t_json_value *m,
								t_json_value_type t, t_textures_holder *th)
{
	t_json_array	*ar;
	unsigned long	i;

	(void)t;
	if (!ft_json_test_type(m, array))
		return ;
	ar = (t_json_array*)m->ptr;
	i = 0;
	while (i < ar->nb_values)
	{
		parse_image(ft_json_acces_value(ar->value[i], NULL, "oo", "texture",
			"file"), th);
		parse_image(ft_json_acces_value(ar->value[i++], NULL, "oo",
			"normal_map","file"), th);
	}
}*/

inline static void	parse_primitive_group_images(t_json_array *ar,
											t_textures_holder *textures)
{
	unsigned long	i;

	i = -1;
	(void)ar;
	(void)textures;
	// while (++i < ar->nb_values)
	// 	ft_json_accesses(ar->value[i], "ro>>s#ro>>s#", "texture", "file",
	// 		parse_image, textures, "normal_map", "file", parse_image, textures);
}

/*
void				parse_images(t_json_value *root,
								t_textures_holder *textures)
{
	t_json_value	*v;
	t_json_object	*obj;
	unsigned long	i;

	v = ft_json_search_pair_in_object(root, ft_json_s_string("materials"));
	if (v != NULL && v->type == object && (obj = (t_json_object*)v->ptr) != NULL
			&& obj->nb_pairs != 0 && obj->pair != NULL && (i = -1))
		while (++i < obj->nb_pairs)
			if (obj->pair[i] != NULL)
			{
				parse_image(ft_json_acces_value(obj->pair[i]->value, NULL, "oo",
					"texture", "file"), textures);
				parse_image(ft_json_acces_value(obj->pair[i]->value, NULL, "oo",
					"normal_map", "file"), textures);
			}
	parse_primitive_group_images(ft_json_search_pair_in_object(root,
		ft_json_s_string("objects")), textures);
	v = ft_json_search_pair_in_object(root, ft_json_s_string("group"));
	if (v != NULL && v->type == object && (obj = (t_json_object*)v->ptr) != NULL
			&& obj->nb_pairs != 0 && obj->pair != NULL && (i = -1))
		while (++i < obj->nb_pairs)
			if (obj->pair[i] != NULL)
				parse_primitive_group_images(obj->pair[i]->value, textures);
	parse_image(ft_json_acces_value(root, NULL, "ooo", "render_options",
		"skybox", "file"), textures);
}
*/

void				parse_images(t_json_value *root,
								t_textures_holder *textures)
{
	t_json_object	*obj;
	unsigned long	i;

	obj = NULL;
	ft_json_accesses(root, "ro>*", "materials", &obj);
	if (obj != NULL && obj->pair != NULL && (i = -1))
		while (++i < obj->nb_pairs)
			if (obj->pair[i] != NULL && ft_json_test_type(obj->pair[i]->value, object))
				ft_json_accesses(obj->pair[i]->value, "ro>>s#ro>>s#", "texture",
					"file", parse_image, textures, "normal_map", "file",
					parse_image, textures);
	ft_json_accesses(root, "ro>a#", "objects", parse_primitive_group_images,
		textures);
	obj = NULL;
	ft_json_accesses(root, "ro>*", "group", &obj);
	if (obj != NULL && obj->pair != NULL && (i = -1))
		while (++i < obj->nb_pairs)
			if (obj->pair[i] != NULL &&
					ft_json_test_type(obj->pair[i]->value, array))
				parse_primitive_group_images(obj->pair[i]->value->ptr, textures);
	ft_json_accesses(root, "ro>>>s#", "render_options", "skybox", "file",
		parse_image, textures);
}
