/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 11:27:40 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/11 16:59:31 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static void		cl_update_kernel_args(t_cl_ctx *ctx, t_cl_kernel *ker)
{
	t_cl_param	*params;
	int			i;

	i = 0;
	params = ker->params;
	while (i < ker->p_count)
	{
		if (params->flags & PARAM_CPY && (params->needs_update ||
			params->flags & ALWAYS_UPDATE))
		{
			ft_printf("%d : %p\n", i, params->p);
			clEnqueueWriteBuffer(ctx->queue, params->mem, CL_TRUE, 0,
				params->size, params->p, 0, NULL, NULL);
			params->needs_update = 0;	
		}
		params++;
		i++;
	}
	clFinish(ctx->queue);
}

void			run_kernel(void *env, t_cl_ctx *ctx, t_cl_kernel *ker,
	void (*process)(void *, t_cl_param *, int))
{
	cl_update_kernel_args(ctx, ker);
	clEnqueueNDRangeKernel(ctx->queue, ker->kernel, ker->dim, NULL,
		ker->global, ker->local, 0, NULL, NULL);
	clFinish(ctx->queue);
	process(env, ker->params, ker->p_count);
}
