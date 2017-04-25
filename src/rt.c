/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:40:29 by hmartzol          #+#    #+#             */
/*   Updated: 2017/04/14 15:37:42 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <mlx.h>

void	percent_callback(int percent, t_env *e)
{
	int y;
	int chunk;

	if (e->cmd.progress_bar_toggle)
	{
		y = 0;
		chunk = (int)(e->argn.screen_size.x / 100);
		while (y < 16)
		{
			ftx_horizontal_line(ftx_data()->focused_window->vbuffer,
		ft_point(chunk * MAX(percent - 1, 0), y), ft_point(chunk * percent, y),
		ft_point(0xFF6619, 0xFF6619));
			y++;
		}
		if (percent % 1 == 0)
		{
			ftx_refresh_window(ftx_data()->focused_window);
			mlx_do_sync(ftx_data()->mlx);
		}
	}
}

void	test_file_update(t_env *e)
{
	struct stat	tstatus;

	stat(e->cmd.scene, &tstatus);
	if (tstatus.st_mtimespec.tv_sec != e->cmd.status.st_mtimespec.tv_sec)
	{
		load_file(e, e->cmd.scene);
		e->keys.updated = 1;
		opencl_render(e);
	}
}

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
		test_file_update(e);
	}
}

void	rt(t_env *e)
{
	e->argn.moving = 1;
	e->keys.updated = 0;
	glfwSetCursorPos(e->glfw.win, e->mouse.x, e->mouse.y);
	while (!glfwWindowShouldClose(e->glfw.win))
	{
		display_fps(e, e->glfw.win, e->glfw.win_name);

		glfwPollEvents();
		handle_keys(e->glfw.keys, e);
		if (e->argn.moving)
			e->argn.antialias = 1;
		if (e->need_reboot)
		{
			e->need_reboot = 0;
			ft_printf("Rebooting application...\n");
			load_file(e, e->cmd.scene);
		}
		if (e->glfw.focus)
			opencl_render(e);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(e->glfw.vao);
		glUseProgram(e->glfw.program);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(e->glfw.win);
		e->argn.moving = 0;
	}
}
