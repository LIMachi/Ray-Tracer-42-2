/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 10:37:52 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/04 10:37:52 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_cl_param		cl_create_param(int mem_type, size_t size, void *p, int flags)
{
	if (flags & PARAM_MEM)
		return ((t_cl_param){0, (cl_mem)p, sizeof(cl_mem), mem_type, flags, 1});
	return ((t_cl_param){p, 0, size, mem_type, flags, 1});
}

t_cl_kernel		*cl_create_kernel(t_cl_ctx *ctx, char *name, int dim)
{
	int			err;
	t_cl_kernel	ker;

	ft_bzero(&ker, sizeof(t_cl_kernel));
	ker.name = ft_strdup(name);
	ker.dim = dim;
	ker.kernel = clCreateKernel(ctx->program, name, &err);
	if (err)
		ft_dprintf(2, "error creating kernel %s\n", name);
	ft_pushback((void **)&ctx->kernels, sizeof(t_cl_kernel), ctx->k_count++,
		&ker);
	return (ctx->kernels + (ctx->k_count - 1));
}

void			cl_set_kernel_dims(t_cl_kernel *ker, size_t *g, size_t *l)
{
	if (ker->global)
		ft_free(ker->global);
	if (ker->local)
		ft_free(ker->local);		
	if (g)
	{
		ker->global = ft_malloc(sizeof(size_t) * ker->dim);
		ft_memcpy(ker->global, g, sizeof(size_t) * ker->dim);
	}
	if (l)
	{
		ker->local = ft_malloc(sizeof(size_t) * ker->dim);
		ft_memcpy(ker->local, l, sizeof(size_t) * ker->dim);
	}
}

void			cl_init_kernel(t_cl_ctx *ctx, t_cl_kernel *ker,
	t_cl_param *params, int n)
{
	int		err;
	int		i;

	ker->params = params;
	ker->p_count = n;
	i = 0;
	while (i < n)
	{
		if (params->flags & (PARAM_CPY | PARAM_BUFFER))
		{
			params->mem = clCreateBuffer(ctx->ctx, params->mem_type,
				params->size, NULL, &err);
			if (err)
				ft_dprintf(2, "error creating mem buffer for kernel %s\n",
					ker->name);
		}
		clSetKernelArg(ker->kernel, i, params->flags ? sizeof(cl_mem) :
			params->size, params->flags ? &params->mem : params->p);
		params++;
		i++;
	}
	clFinish(ctx->queue);
}
