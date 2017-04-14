/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 09:15:54 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/25 23:47:50 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include "mlx.h"

void	display_fps(t_env *e, GLFWwindow *win, char *name)
{
	static int		frames = 0;
	static double	t0 = 0;
	double			t1;

	t1 = glfwGetTime();
	frames++;
	if (t1 - t0 > 1.0)
	{
		t0 = t1;
		if (e->glfw.fps != frames)
		{
			name = ft_strjoin(name, " : ");
			name = ft_strmergeflag(name, ft_itoa(frames), 3);
			name = ft_strmergeflag(name, " fps", 1);
			glfwSetWindowTitle(win, name);
			ft_free(name);
			e->glfw.fps = frames;
		}
		frames = 0;
	}
}

void		rt(t_env *e)
{
	e->keys.updated = 1;
	glfwGetCursorPos(e->glfw.win, &e->mouse.x, &e->mouse.y);
	while (!glfwWindowShouldClose(e->glfw.win))
	{
		display_fps(e, e->glfw.win, e->glfw.win_name);
		glfwPollEvents();
		handle_keys(e->glfw.keys, e);
		// opencl_render(e);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(e->glfw.vao);
		glUseProgram(e->glfw.program);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(e->glfw.win);
	}
}

void		init(t_env *e, char *src)
{
	int		fd;

	if ((fd = open(e->cmd.scene, O_RDONLY)) == -1)
		ft_end(-1);
	e->cam.orientation.r = 1;
	e->glfw.fps = 60;
	parser(e, src = ft_readfile(fd));
	close(fd);
	ft_free(src);
	calc_vpul(&e->cam);
	e->window = ft_point(e->argn.screen_size.x, e->argn.screen_size.y);
	e->glfw.win = glfw_init(e, "RT", e->window.x, e->window.y);
	glewExperimental = GL_TRUE;
	glewInit();
	init_vao(&e->glfw.vao);
	init_shaders(e->glfw.vao, &e->glfw.program, "shaders/lemin.vs", "shaders/lemin.fs");
	init_texture(&e->glfw.tex, e->window.x, e->window.y);
	glfwMakeContextCurrent(e->glfw.win);
	e->glfw.cl_ctx = init_cl_context("scl/raytracer.cl", NULL,
		CL_DEVICE_TYPE_GPU, INTEROP_TRUE);
	opencl_init(e);
	if (e->cmd.output != NULL)
		direct_output(&e->out, &e->argn, e->cmd.output);
}

int			main(const int argc, char **argv, char **env)
{
	t_env	e;
	char	*src;

	src = NULL;
	ft_bzero(&e, sizeof(t_env));
	ft_init(env);
	if (command_line(&e.cmd, argc, argv))
	{
		ft_printf("\nUsage: \t%s/%s <scene.json>\n\n", ft_pwd(),
		ft_path_name(argv[0]));
		ft_end(0);
	}
	init(&e, src);
	rt(&e);
	ft_end(0);
}
