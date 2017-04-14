/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 04:13:55 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/13 04:13:55 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>


t_material_holder	*materials(void)
{
	static t_material_holder	m = {.nb_materials = 0, .name = NULL,

	.materials = NULL};
	return (&m);
}

t_camera	*cam(void)
{
	static t_camera	cam = {

	.pos = {.x = 0, .y = 0, .z = 0, .w = 0},
	.dir = {.x = 0, .y = 0, .z = 1, .w = 0},
	.up = {.x = 0, .y = 1, .z = 0, .w = 0},
	.right = {.x = 1, .y = 0, .z = 0, .w = 0},
	.vpul = {.x = 0, .y = 0, .z = 0, .w = 0},
	.vp_size = {.x = 0, .y = 0},
	.dist = 0,
	.orientation = {.r = 1, .i = 0, .j = 0, .k = 0}};
	return (&cam);
}

t_argn	*argn(void)
{
	static t_argn	argn;

	return (&argn);
}

t_primitive	**prim(void)
{
	static t_primitive	*prim = NULL;

	return (&prim);
}

t_ubmp	*out(void)
{
	static t_ubmp		out = {.size = {.x = 0, .y = 0}, .data = NULL};

	return (&out);
}

t_ubmp	*prim_map(void)
{
	static t_ubmp		out = {.size = {.x = 0, .y = 0}, .data = NULL};

	return (&out);
}


t_light	**lights(void)
{
	static t_light	*data = NULL;

	return (&data);
}


t_textures_holder	*textures_holder(void)
{
	static t_textures_holder	th = {.nb_info = 0, .path = NULL,

	.info = NULL, .total_raw_size = 0, .raw_bmp = NULL};
	return (&th);
}
