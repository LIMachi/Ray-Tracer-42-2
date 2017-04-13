/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scroll.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 00:19:35 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/14 00:19:36 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	mouse_scroll_callback(GLFWwindow* window, double dx, double dy)
{
	t_env	*e;
	int		check;
	int		x;
	int		y;

	(void)dx;
	(void)window;
	e = glfw_env(NULL);
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
