/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 10:32:27 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/04 10:32:28 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  <rt.h>

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
	add_param(cl_create_param(RD, sizeof(cl_int) * e->textures.total_raw_size,
		e->textures.raw_bmp, PARAM_CPY), &t, n);
	return (t);
}

void		opencl_init(t_env *e)
{
	t_cl_param	*t;
	int			n;
	int			i;
	size_t		g[2];
	int			err;
	
	n = 0;
	g[0] = e->window.x;
	g[1] = e->window.y;
	e->glfw.render = cl_create_kernel(&e->glfw.cl_ctx, "rt_kernel", 2);
	cl_set_kernel_dims(e->glfw.render, g, NULL);
	e->glfw.cl_tex = clCreateFromGLTexture(e->glfw.cl_ctx.ctx,
		CL_MEM_WRITE_ONLY, GL_TEXTURE_2D, 0, e->glfw.tex, &err);
	if (err)
		ft_error(EINVAL, "couldnt create cl_mem from texture\n");
	else
		ft_printf("created mem object : %p\n", e->glfw.cl_tex);
	t = build_params(e, &n, g);
	i = 0;
	while (i < n)
	{
		t[i].needs_update = !!(t[i].flags & PARAM_CPY);
		i++;
	}
	cl_init_kernel(&e->glfw.cl_ctx, e->glfw.render, t, n);
}
