/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glfw_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 23:54:53 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/13 23:54:53 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>


static void		rotate(t_env *e, double x, double y)
{
	t_quaternion	q;
	t_vector		d;
	t_vector		r;
	const t_vector	vects[] = {{0, 1, 0}, {1, 0, 0}};

	d = ft_vector(e->cam.dir.x, e->cam.dir.y, e->cam.dir.z);
	r = ft_vector(e->cam.dir.x, e->cam.dir.y, e->cam.dir.z);
	if (x)
	{
		q = ft_quat_rotation_build(x * ROT, vects[1]);
		ft_quat_conjugation(q, &d);
		ft_quat_conjugation(q, &r);
	}
	if (y)
	{
		q = ft_quat_rotation_build(-y * ROT, vects[0]);
		ft_quat_conjugation(q, &d);
		ft_quat_conjugation(q, &r);
	}
	e->cam.dir = (cl_float4){.v4 = {d.x, d.y, d.z, 0}};
	e->cam.right = (cl_float4){.v4 = {r.x, r.y, r.z, 0}};
	d = ft_vector_cross_product(d, r);
	e->cam.up = (cl_float4){.v4 = {d.x, d.y, d.z, 0}};
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
	if (e->mouse.is_select > 0)
	{
		new_pos(&e->prim[e->mouse.is_select - 1].position, x, y, e);
		ftocl_clear_current_kernel_arg(3);
		ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 3, sizeof(t_primitive) *
		e->argn.nb_objects, (void*)e->prim);
	}
	else
	{
		new_pos(&e->lights[-e->mouse.is_select - 1].position, x, y, e);
		ftocl_clear_current_kernel_arg(4);
		ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 4, sizeof(t_light) *
			e->argn.nb_lights, (void*)e->lights);
	}
}

void			mouse_callback(GLFWwindow* window, double x, double y)
{
	t_env	*e;

	e = glfw_env(NULL);
	(void)window;
	if (!e->mouse.is_select)
		rotate(e, x - e->mouse.x, y - e->mouse.y);
	else
		mouse_drag(e, x, y);
	e->mouse.x = x;
	e->mouse.y = y;
	e->keys.updated = 1;
}
