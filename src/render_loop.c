/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 01:19:11 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/14 01:19:12 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	process_ker_ret(t_env *e, t_cl_param *params, int n)
{
	(void)params;
	(void)n;
	clFinish(e->glfw.cl_ctx.queue);
	clEnqueueReleaseGLObjects(e->glfw.cl_ctx.queue, 1,
		&e->glfw.cl_tex, 0, 0, NULL);
}

void	opencl_render(t_env *e, t_ctx_glfw *glfw)
{
	glFinish();
	clEnqueueAcquireGLObjects(glfw->cl_ctx.queue, 1, &glfw->cl_tex, 0, 0,
		NULL);
	run_kernel(e, &glfw->cl_ctx, glfw->render, (t_f_cl_proc)process_ker_ret);
}

void	handle_keys(t_key *keys, t_env *e)
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
