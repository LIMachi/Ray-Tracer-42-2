/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 01:19:11 by cchaumar          #+#    #+#             */
/*   Updated: 2017/05/24 06:17:16 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		process_ker_ret(t_env *e, t_cl_param *params, int n)
{
	(void)params;
	(void)n;
	clFinish(e->glfw.cl_ctx.queue);
	clEnqueueReleaseGLObjects(e->glfw.cl_ctx.queue, 1,
		&e->glfw.cl_tex, 0, 0, NULL);
}

void		opencl_render(t_env *e)
{
	size_t	g[2];

	if (e->argn.moving != e->keys.updated)
	{
		g[0] = e->window.x / (1 + e->argn.moving);
		g[1] = e->window.y / (1 + e->argn.moving);
		e->glfw.render->params[2].needs_update = 1;
		cl_set_kernel_dims(e->glfw.render, g, NULL);
	}
	if (e->keys.updated)
	{
		glFinish();
		clEnqueueAcquireGLObjects(e->glfw.cl_ctx.queue, 1,
			&e->glfw.cl_tex, 0, 0, NULL);
		run_kernel(e, &e->glfw.cl_ctx,
			e->glfw.render, (t_f_cl_proc)process_ker_ret);
	}
	e->keys.updated = e->argn.moving;
//	debug(e);
}

void		handle_keys(t_key *keys, t_env *e)
{
	int	i;

	i = 0;
	while (i < e->glfw.nkeys)
	{
		if (keys->pressed && keys->repeat)
			keys->repeat(e, keys->keycode);
		i++;
		keys++;
	}
}
