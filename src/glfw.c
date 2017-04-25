/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 01:07:41 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/14 15:39:52 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static void	glfw_error(int err, const char *desc)
{
	ft_dprintf(2, "error (%d) : %s\n", err, desc);
}

static void	glfw_resize(GLFWwindow *win, int w, int h)
{
	(void)win;
	glfw_env(NULL)->window = (t_point){w, h};
}

void		framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
}

void		glfw_init0(t_env *e, GLFWwindow *win)
{
	glfwMakeContextCurrent(win);
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSwapInterval(1);
	set_keys(e);
}

GLFWwindow	*glfw_init(t_env *e, char *name, int w, int h)
{
	GLFWwindow *win;

	glfwSetErrorCallback(glfw_error);
	if (!glfwInit())
		die(EINVAL, "Couldn't start glfw\n", NULL);
	glfw_env(e);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (!(win = glfwCreateWindow(w, h, name, NULL, NULL)))
		die(EINVAL, "Couldn't create window\n", NULL);
	glfwSetKeyCallback(win, (GLFWkeyfun)key_callback);
	glfwSetCursorPosCallback(win, mouse_callback);
	glfwSetMouseButtonCallback(win, mouse_button_callback);
	glfwSetScrollCallback(win, mouse_scroll_callback);
	glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
	glfwSetWindowSizeCallback(win, glfw_resize);
	glfwSetWindowFocusCallback(win, window_focus);
	glfwSetDropCallback(win, file_drop_callback);
	glfw_init0(e, win);
	return (win);
}
