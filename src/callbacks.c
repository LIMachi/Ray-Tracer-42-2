/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 01:48:18 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/14 15:16:44 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int			key_match(int keycode, int action, t_key *key)
{
	if (key->keycode == keycode)
	{
		key->pressed = action != RELEASE ? 1 : 0;
		if (key->press && action == PRESS)
			key->press(glfw_env(NULL), keycode);
		if (key->release && action == RELEASE)
			key->release(glfw_env(NULL), keycode);
		return (1);
	}
	return (0);
}

void		key_callback(GLFWwindow *win, int key, int scan, int action)
{
	t_env	*e;
	int		i;
	t_key	*keys;

	e = glfw_env(NULL);
	(void)win;
	(void)scan;
	keys = e->glfw.keys;
	i = 0;
	while (i < e->glfw.nkeys)
	{
		if (key_match(key, action, keys))
			return ;
		keys++;
		i++;
	}
}

void		window_focus(GLFWwindow *win, int focus)
{
	(void)win;
	glfw_env(NULL)->glfw.focus = focus == GLFW_TRUE;
}

void		load_file(t_env *e, const char *path)
{
	int			fd;
	char		*src;
	char		*tmp;
	t_camera	cam;

	fd = -1;
	if (path == NULL || (fd = open(path, O_RDONLY)) == -1 ||
		(src = ft_readfile(fd)) == NULL)
	{
		if (fd != -1)
			close(fd);
		return ;
	}
	cam = e->cam;
	tmp = ft_strdup(path);
	delete_rt_environement(e);
	e->cmd.scene = tmp;
	parser(e, src);
	ft_free(src);
	close(fd);
	stat(e->cmd.scene, &e->cmd.status);
	opencl_init(e, (size_t[2]){e->window.x, e->window.y});
	e->cam = cam;
}

void		file_drop_callback(GLFWwindow *win, int n, const char **paths)
{
	t_env	*e;

	(void)n;
	if (paths == NULL)
		return ;
	e = glfw_env(NULL);
	load_file(e, *paths);
	glfwFocusWindow(win);
	toggle_cursor(e, 0);
}
