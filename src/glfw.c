/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 01:07:41 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/03 01:07:41 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_env			*glfw_env(t_env *e)
{
	static t_env	*pe = NULL;

	return ((pe = e ? e : pe));
}

static void		glfw_error(int err, const char* desc)
{
	ft_dprintf(2, "error (%d) : %s\n", err, desc);
}

static void	glfw_resize(GLFWwindow *win, int w, int h)
{
	(void)win;
	glfw_env(NULL)->window = (t_point){w, h};
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	(void)window;
	glViewport(0, 0, width, height);
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
 	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if (!(win = glfwCreateWindow(w, h, name, NULL, NULL)))
		die(EINVAL, "Couldn't create window\n", NULL);
	glfwSetKeyCallback(win, key_callback);
	glfwSetCursorPosCallback(win, mouse_callback);
	glfwSetMouseButtonCallback(win, mouse_button_callback);
	glfwSetScrollCallback(win, mouse_scroll_callback);
	glfwSetFramebufferSizeCallback(win, framebuffer_size_callback);
	glfwSetWindowSizeCallback(win, glfw_resize);
	glfwMakeContextCurrent(win);
	glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSwapInterval(1);
	set_keys(e);
	return (win);
}
