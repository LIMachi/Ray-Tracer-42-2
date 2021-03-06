/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opencl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 20:09:50 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/11 16:58:55 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_callback		notify(const char *errinfo, const void *private_info,
		size_t cb, void *user_data)
{
	static int		errcount = 0;

	(void)private_info;
	(void)cb;
	(void)user_data;
	ft_printf("Error %d (notified) : %s\n", ++errcount, errinfo);
	if (!ft_strcmp("[CL_INVALID_VALUE] : OpenCL Error : clEnqueueReadBuffer fai"
			"led: unable to allocate enough temporary memory to facilitate the "
			"data transfer", (char*)errinfo))
		glfw_env(NULL)->need_reboot = 1;
}

cl_program		build_program(cl_context ctx, char *source_file)
{
	char	*source;
	int		fd;

	if ((fd = open(source_file, O_RDONLY)) == -1)
		return (NULL);
	if (!(source = ft_readfile(fd)))
		return (NULL);
	close(fd);
	return (clCreateProgramWithSource(ctx, 1, (const char **)&source, NULL,
		NULL));
}

cl_context		create_context(cl_device_id *dev, int inter)
{
	CGLContextObj			gl_ctx;
	CGLShareGroupObj		gl_sharegroup;
	cl_context_properties	properties[3];

	if (inter)
	{
		gl_ctx = CGLGetCurrentContext();
		gl_sharegroup = CGLGetShareGroup(gl_ctx);
		properties[0] = CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE;
		properties[1] = (cl_context_properties)gl_sharegroup;
		properties[2] = 0;
	}
	return (clCreateContext(inter ? properties : NULL, 1, dev, notify, NULL,
		NULL));
}

t_cl_ctx		init_cl_context(char *source, char *opts, int type, int inter)
{
	t_cl_ctx				ctx;

	ft_bzero(&ctx, sizeof(t_cl_ctx));
	ctx.device = select_device(type);
	if (!(ctx.ctx = create_context(&ctx.device, inter)))
		ft_error(EINVAL, "Can't create context\n");
	if (!(ctx.queue = clCreateCommandQueue(ctx.ctx, ctx.device, 0, NULL)))
		ft_error(EINVAL, "Can't create queue\n");
	if (!(ctx.program = build_program(ctx.ctx, source)))
		ft_error(EINVAL, "Can't create program\n");
	if (clBuildProgram(ctx.program, 1, &ctx.device, opts, NULL, NULL))
		ft_error(EINVAL, "Can't build program\n");
	return (ctx);
}
