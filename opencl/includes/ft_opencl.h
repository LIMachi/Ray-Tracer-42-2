/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opencl.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 20:10:13 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/11 16:56:52 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OPENCL_H
# define FT_OPENCL_H

# include "../../libft.h"
# include <OpenCL/cl.h>
# include <OpenCL/cl_gl_ext.h>
# include <OpenGL/OpenGL.h>

# define SIZE_MO		1048576
# define CLCB			void CL_CALLBACK
# define INTEROP_TRUE	1
# define INTEROP_FALSE	0
# define PARAM_MEM		2
# define PARAM_CPY		1
# define PARAM_NO_CPY	0
# define CL_WRONLY		CL_MEM_WRITE_ONLY
# define CL_RDONLY		CL_MEM_READ_ONLY
# define CL_RW			CL_MEM_READ_WRITE

typedef cl_command_queue	t_cl_queue;
typedef CLCB				t_callback;

typedef struct	s_cl_param
{
	void	*p;
	cl_mem	mem;
	size_t	size;
	int		mem_type;
	int		flags;
}				t_cl_param;

typedef struct	s_cl_kernel
{
	char		*name;
	cl_kernel	kernel;
	t_cl_param	*params;
	size_t		*global;
	size_t		*local;
	int			dim;
	int			p_count;
}				t_cl_kernel;

typedef struct	s_cl_ctx
{
	cl_device_id	device;
	cl_context		ctx;
	t_cl_queue		queue;
	cl_program		program;
	t_cl_kernel		*kernels;
	int				k_count;
}				t_cl_ctx;

typedef void	(*t_f_cl_proc)(void *, t_cl_param *, int);

t_cl_ctx		init_cl_context(char *source, char *opts, int type, int inter);
t_cl_param		cl_create_param(int mem_type, size_t size, void *p, int flags);
t_cl_kernel		*cl_create_kernel(t_cl_ctx *ctx, char *name, int dim);
void			cl_init_kernel(t_cl_ctx *ctx, t_cl_kernel *ker,
	t_cl_param *params, int n);
void			cl_set_kernel_dims(t_cl_kernel *ker, size_t *g, size_t *l);
void			run_kernel_name(void *env, t_cl_ctx *ctx, char *name,
	void (*process)(void *, t_cl_param *, int));
void			run_kernel(void *env, t_cl_ctx *ctx, t_cl_kernel *ker,
	void (*process)(void *, t_cl_param *, int));

cl_device_id	select_device(int type);

#endif
