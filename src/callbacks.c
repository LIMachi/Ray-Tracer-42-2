/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   callbacks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 01:48:18 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/03 01:48:19 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static int	key_match(int keycode, int action, t_key *key)
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

void		key_callback(GLFWwindow* win, int key, int scan, int action,
	int mods)
{
	t_env	*e;
	int		i;
	t_key	*keys;

	e = glfw_env(NULL);
	(void)win;
	(void)mods;
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

void		mouse_click(t_env *e, int key)
{
	int	check;
	int	x;
	int	y;

	x = e->mouse.x;
	y = e->mouse.y;
	if (!(x >= 0 && y >= 0 && x < e->prim_map.size.x && y < e->prim_map.size.y))
		return ;
	check = e->prim_map.data[e->prim_map.size.x * y + x];
	if (key == 1)
		e->mouse.is_select = check;
	ftocl_clear_current_kernel_arg(3);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 3, sizeof(t_primitive) *
		e->argn.nb_objects, (void*)e->prim);
	e->keys.updated = 1;
}

void		mouse_off(t_env *e, int key)
{
	if (key == GLFW_MOUSE_BUTTON_LEFT)
		e->mouse.is_select = 0;
	e->keys.updated = 1;
}

void 		mouse_button_callback(GLFWwindow* window,
	int button, int action, int mods)
{
	t_env	*e;
	int		i;
	t_key	*keys;

	e = glfw_env(NULL);
	(void)window;
	(void)mods;
	keys = e->glfw.mkeys;
	i = 0;
	while (i < e->glfw.nmkeys)
	{
		if (key_match(button, action, keys))
			return ;
		keys++;
		i++;
	}
}
