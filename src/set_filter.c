/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 15:26:09 by hmartzol          #+#    #+#             */
/*   Updated: 2017/04/14 15:27:29 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		filter_sepia(t_env *e, int keycode)
{
	keycode = keycode + 32;
	e->glfw.render->params[2].needs_update = 1;
	e->argn.filter = 1;
}

void		filter_cartoon(t_env *e, int keycode)
{
	keycode = keycode + 32;
	e->glfw.render->params[2].needs_update = 1;
	e->argn.filter = 3;
}

void		filter_gray(t_env *e, int keycode)
{
	keycode = keycode + 32;
	e->glfw.render->params[2].needs_update = 1;
	e->argn.filter = 2;
}

void		filter_none(t_env *e, int keycode)
{
	keycode = keycode + 32;
	e->glfw.render->params[2].needs_update = 1;
	e->argn.filter = 0;
}
