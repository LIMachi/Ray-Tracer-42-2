/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 19:03:16 by hmartzol          #+#    #+#             */
/*   Updated: 2017/03/08 04:14:15 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

int			mouse_click(int key, int x, int y, t_env *e)
{
	int check;

	if (!(x >= 0 && y >= 0 && x < e->prim_map.size.x && y < e->prim_map.size.y))
		return (0);
	check = e->prim_map.data[e->prim_map.size.x * y + x];
	if (check > 0 && key == 4)
		e->prim[check - 1].radius *= 1.04f;
	if (check > 0 && key == 5)
		e->prim[check - 1].radius /= 1.04f;
	if (key == 1)
		e->mouse.is_select = check;
	ftocl_clear_current_kernel_arg(3);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 3, sizeof(t_primitive) *
		e->argn.nb_objects, (void*)e->prim);
	e->keys.updated = 1;
	update(e);
	return (0);
}

int			mouse_off(int key, int x, int y, t_mouse *mouse)
{
	(void)x;
	(void)y;
	if (key == 1)
		mouse->is_select = 0;
	return (0);
}

void		new_pos(cl_float4 *item_pos, int x, int y, t_env *e)
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

int			mouse_move(int x, int y, t_env *e)
{
	static int upd = 0;

	if (!e->mouse.is_select)
		return (0);
	upd++;
	if (upd != UPD || (upd = 0))
		return (0);
	if (e->mouse.is_select > 0)
	{
		new_pos(&e->prim[e->mouse.is_select - 1].position, x, y, e);
		ftocl_clear_current_kernel_arg(3);
		ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 3, sizeof(t_primitive) *
		e->argn.nb_objects, (void*)*prim());
	}
	else
	{
		new_pos(&lights()[0][-e->mouse.is_select - 1].position, x, y, e);
		ftocl_clear_current_kernel_arg(4);
		ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 4, sizeof(t_light) *
			e->argn.nb_lights, (void*)*lights());
	}
	e->mouse.x = x;
	e->mouse.y = y;
	e->keys.updated = 1;
	update(e);
	return (0);
}
