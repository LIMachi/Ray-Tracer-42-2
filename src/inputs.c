/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 01:10:07 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/14 15:29:09 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static void		add_key(t_env *e, int keycode, t_key_f press, t_key_f repeat)
{
	t_key	key;

	key = (t_key){keycode, 0, press, repeat, NULL};
	ft_pushback((void **)&e->glfw.keys, sizeof(t_key), e->glfw.nkeys++, &key);
}

static void		add_mouse_key(t_env *e, int button,
	t_key_f press, t_key_f release)
{
	t_key	key;

	key = (t_key){button, 0, press, NULL, release};
	ft_pushback((void **)&e->glfw.mkeys, sizeof(t_key), e->glfw.nmkeys++, &key);
}

static void		quit(t_env *e, int keycode)
{
	(void)keycode;
	glfwSetWindowShouldClose(e->glfw.win, GLFW_TRUE);
}

static void		move(t_env *e, int keycode)
{
	t_vector	v;

	if (keycode == GLFW_KEY_A)
		v = ft_vector_scale(cl_float4_to_vector(e->cam.right), -1);
	else if (keycode == GLFW_KEY_S)
		v = ft_vector_scale(cl_float4_to_vector(e->cam.dir), -1);
	else if (keycode == GLFW_KEY_LEFT_SHIFT)
		v = ft_vector_scale(cl_float4_to_vector(e->cam.up), -1);
	else if (keycode == GLFW_KEY_D)
		v = cl_float4_to_vector(e->cam.right);
	else if (keycode == GLFW_KEY_W)
		v = cl_float4_to_vector(e->cam.dir);
	else if (keycode == GLFW_KEY_SPACE)
		v = cl_float4_to_vector(e->cam.up);
	else
		return ;
	e->cam.pos = vector_to_cl_float4(ft_vector_add(
		cl_float4_to_vector(e->cam.pos),
		ft_vector_scale(v, SPEED * 60.0f / e->glfw.fps)));
}

void			set_keys(t_env *e)
{
	add_key(e, GLFW_KEY_ESCAPE, quit, NULL);
	add_key(e, GLFW_KEY_A, NULL, move);
	add_key(e, GLFW_KEY_S, NULL, move);
	add_key(e, GLFW_KEY_D, NULL, move);
	add_key(e, GLFW_KEY_SPACE, NULL, move);
	add_key(e, GLFW_KEY_LEFT_SHIFT, NULL, move);
	add_key(e, GLFW_KEY_W, NULL, move);
	add_key(e, GLFW_KEY_LEFT_ALT, toggle_cursor, NULL);
	add_key(e, GLFW_KEY_1, filter_sepia, NULL);
	add_key(e, GLFW_KEY_2, filter_gray, NULL);
	add_key(e, GLFW_KEY_3, filter_cartoon, NULL);
	add_key(e, GLFW_KEY_4, filter_none, NULL);
	add_mouse_key(e, GLFW_MOUSE_BUTTON_LEFT, mouse_click, mouse_off);
}
