/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 09:15:54 by hmartzol          #+#    #+#             */
/*   Updated: 2017/04/14 15:37:06 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include "mlx.h"

void	kernel_init(t_env *e)
{
	int			err;

	e->glfw.render = cl_create_kernel(&e->glfw.cl_ctx, "rt_kernel", 2);
	cl_set_kernel_dims(e->glfw.render,
		(size_t[2]){e->window.x, e->window.y}, NULL);
	e->glfw.cl_tex = clCreateFromGLTexture(e->glfw.cl_ctx.ctx,
		CL_MEM_WRITE_ONLY, GL_TEXTURE_2D, 0, e->glfw.tex, &err);
	if (err)
		ft_error(EINVAL, "couldnt create cl_mem from texture\n");
	else
		ft_printf("created mem object : %p\n", e->glfw.cl_tex);
	opencl_init(e, (size_t[2]){e->window.x, e->window.y});
}

void	init(t_env *e)
{
	size_t	size;

	calc_vpul(&e->cam);
	e->glfw.focus = 1;
	e->window = ft_point(e->argn.screen_size.x, e->argn.screen_size.y);
	size = e->window.x * e->window.y;
	e->prim_map = (t_ubmp){e->window, ft_malloc(size * 4)};
	e->glfw.win = glfw_init(e, "RT", e->window.x, e->window.y);
	glewExperimental = GL_TRUE;
	glewInit();
	glfwMakeContextCurrent(e->glfw.win);
	init_vao(&e->glfw.vao);
	init_shaders(e->glfw.vao, &e->glfw.program, "shaders/lemin.vs",
		"shaders/lemin.fs");
	init_texture(e->glfw.vao, &e->glfw.tex, e->window.x, e->window.y);
	e->glfw.cl_ctx = init_cl_context("scl/raytracer.cl", NULL,
		CL_DEVICE_TYPE_GPU, INTEROP_TRUE);
	kernel_init(e);
}

int		main(const int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	t_env	e;
	char	*src;
	int		fd;

	src = NULL;
	ft_bzero(&e, sizeof(t_env));
	ft_init(env);
/*	if (command_line(&e.cmd, argc, argv))
	{
		ft_printf("\nUsage: \t%s/%s <scene.json>\n\n", ft_pwd(),
		ft_path_name(argv[0]));
		ft_end(0);
	}*/
	if ((fd = open(/*e.cmd.scene*/argv[1], O_RDONLY)) == -1)
		ft_end(-1);
	e.glfw.fps = 60;
	parser(&e, src = ft_readfile(fd));
/*	close(fd);
	stat(e.cmd.scene, &e.cmd.status);
	ft_free(src);
	init(&e);
	rt(&e);
	ft_end(0);
*/
}
