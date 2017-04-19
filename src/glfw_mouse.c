/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 23:54:53 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/14 15:29:06 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

static void		conjug(t_quaternion q, t_vector *d, t_vector *r)
{
	ft_quat_conjugation(q, d);
	ft_quat_conjugation(q, r);	
}

void			rotate(t_env *e, double x, double y, double z)
{
	t_vector		d;
	t_vector		r;
	t_vector		u;

	d = cl_float4_to_vector(e->cam.dir);
	r = cl_float4_to_vector(e->cam.right);
	u = cl_float4_to_vector(e->cam.up);
	
	if (x)
		conjug(ft_quat_rotation_build(x * ROT, u), &d, &r);
	if (y)
		conjug(ft_quat_rotation_build(y * ROT, r), &d, &r);
	if (z)
		conjug(ft_quat_rotation_build(z * ROT, d), &d, &r);
	e->cam.dir = vector_to_cl_float4(d);
	e->cam.right = vector_to_cl_float4(r);
	u = ft_vector_normalize(ft_vector_cross_product(d, r));
	e->cam.up = vector_to_cl_float4(u);
	calc_vpul(&e->cam);
}

static void		new_pos(cl_float4 *item_pos, int x, int y, t_env *e)
{
	*item_pos = cl_float4_add(e->cam.pos, ft_vector_thales(e->cam.pos,
	cl_float4_add(cl_float4_add(cl_float4_scale(e->cam.right,
	(cl_float)(e->mouse.x - e->argn.screen_size.x / 2)),
	cl_float4_scale(e->cam.up,
	-(cl_float)(e->mouse.y - e->argn.screen_size.y / 2))),
	cl_float4_scale(e->cam.dir, e->cam.dist)),
	cl_float4_sub(*item_pos, e->cam.pos), cl_float4_add(cl_float4_add(
	cl_float4_scale(e->cam.right, (cl_float)(x - e->argn.screen_size.x / 2)),
	cl_float4_scale(e->cam.up, -(cl_float)(y - e->argn.screen_size.y / 2))),
	cl_float4_scale(e->cam.dir, e->cam.dist))));
}

static void		mouse_drag(t_env *e, int x, int y)
{
	get_prim_map(e);
	if (e->mouse.is_select > 0)
	{
		new_pos(&e->prim[e->mouse.is_select - 1].position, x, y, e);
		e->glfw.render->params[3].needs_update = 1;
	}
	else
	{
		new_pos(&e->lights[-e->mouse.is_select - 1].position, x, y, e);
		e->glfw.render->params[4].needs_update = 1;
	}
}

void			toggle_cursor(t_env *e, int keycode)
{
	(void)keycode;
	e->keys.cursor = !e->keys.cursor;
	glfwSetInputMode(e->glfw.win, GLFW_CURSOR, e->keys.cursor ?
		GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

void			mouse_callback(GLFWwindow *window, double x, double y)
{
	t_env	*e;

	e = glfw_env(NULL);
	(void)window;
	if (!e->mouse.is_select && !e->keys.cursor)
		rotate(e, x - e->mouse.x, y - e->mouse.y, 0);
	if (e->mouse.is_select && e->keys.cursor)
		mouse_drag(e, x, y);
	e->mouse.x = x;
	e->mouse.y = y;
	e->argn.moving = MOVING;
}
