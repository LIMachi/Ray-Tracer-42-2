/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_funcs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 05:08:04 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/14 05:08:04 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		mouse_click(t_env *e, int key)
{
	int	check;
	int	x;
	int	y;

	x = e->mouse.x;
	y = e->mouse.y;
	if (key != GLFW_MOUSE_BUTTON_LEFT)
		return ;
	get_prim_map(e);
	if (!(x >= 0 && y >= 0 && x < e->prim_map.size.x && y < e->prim_map.size.y))
		return ;
	check = e->prim_map.data[e->prim_map.size.x * y + x];
	e->mouse.is_select = check;
}

void		mouse_off(t_env *e, int key)
{
	if (key == GLFW_MOUSE_BUTTON_LEFT)
		e->mouse.is_select = 0;
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
