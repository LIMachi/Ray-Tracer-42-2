/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 10:32:27 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/14 15:23:02 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		add_param(t_cl_param p, t_cl_param **params, int *n)
{
	ft_pushback((void **)params, sizeof(t_cl_param), (*n)++, &p);
}

t_cl_param	*build_params(t_env *e, int *n, size_t g[])
{
	t_cl_param	*t;

	t = NULL;
	add_param(cl_create_param(WR, 0, e->glfw.cl_tex, PARAM_MEM), &t, n);
	add_param(cl_create_param(WR, sizeof(cl_int) * g[0] * g[1],
		e->prim_map.data, PARAM_CPY), &t, n);
	add_param(cl_create_param(RD, sizeof(t_argn), &e->argn, PARAM_CPY), &t, n);
	add_param(cl_create_param(RD, sizeof(t_primitive) * e->argn.nb_objects,
		e->prim, PARAM_CPY), &t, n);
	add_param(cl_create_param(RD, sizeof(t_light) * e->argn.nb_lights,
		e->lights, PARAM_CPY), &t, n);
	add_param(cl_create_param(RD, sizeof(t_camera), &e->cam, PARAM_CPY |
		ALWAYS_UPDATE), &t, n);
	add_param(cl_create_param(RD, sizeof(t_img_info) * e->argn.nb_info,
		e->textures.info, PARAM_CPY), &t, n);
	add_param(cl_create_param(RD, sizeof(t_material) * e->argn.nb_materials,
		e->materials.materials, PARAM_CPY), &t, n);
	add_param(cl_create_param(RD,
		sizeof(cl_int) * (e->textures.total_raw_size + 1),
		e->textures.raw_bmp, PARAM_CPY), &t, n);
	return (t);
}

void		opencl_init(t_env *e, size_t g[2])
{
	t_cl_param	*t;
	int			n;
	int			i;

	n = 0;
	t = build_params(e, &n, g);
	i = 0;
	while (i < n)
	{
		t[i].needs_update = !!(t[i].flags & PARAM_CPY);
		i++;
	}
	cl_init_kernel(&e->glfw.cl_ctx, e->glfw.render, t, n);
}
