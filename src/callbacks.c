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

int		key_match(int keycode, int action, t_key *key)
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
