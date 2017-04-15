/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <cchaumar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 00:19:35 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/14 15:25:58 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	get_prim_map(t_env *e)
{
	clEnqueueReadBuffer(e->glfw.cl_ctx.queue, e->glfw.render->params[1].mem,
		CL_TRUE, 0, e->prim_map.size.x * e->prim_map.size.y * sizeof(int),
		e->prim_map.data, 0, 0, NULL);
}

void	mouse_scroll_callback(GLFWwindow *window, double dx, double dy)
{
	t_env	*e;
	int		check;
	int		x;
	int		y;

	(void)dx;
	(void)window;
	e = glfw_env(NULL);
	if (!e->keys.cursor)
		return ;
	get_prim_map(e);
	x = e->mouse.x;
	y = e->mouse.y;
	if (!(x >= 0 && y >= 0 && x < e->prim_map.size.x && y < e->prim_map.size.y))
		return ;
	check = e->prim_map.data[e->prim_map.size.x * y + x];
	if (check > 0 && dy > 0)
		e->prim[check - 1].radius *= 1.0f + (dy * SCROLL);
	if (check > 0 && dy < 0)
		e->prim[check - 1].radius /= 1.0f + (dy * SCROLL);
}
