/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 09:40:29 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/30 17:42:30 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <mlx.h>

void		percent_callback(int percent, t_env *e)
{
	int y;
	int chunk;

	if (e->cmd.progress_bar_toggle)
	{
		y = 0;
		chunk = (int)(e->argn.screen_size.x / 100);
		while (y < 16)
		{
			ftx_horizontal_line(ftx_data()->focused_window->vbuffer,
		ft_point(chunk * MAX(percent - 1, 0), y), ft_point(chunk * percent, y),
		ft_point(0xFF6619, 0xFF6619));
			y++;
		}
		if (percent % 1 == 0)
		{
			ftx_refresh_window(ftx_data()->focused_window);
			mlx_do_sync(ftx_data()->mlx);
		}
	}
}

void		update(t_env *e)
{
	size_t size;

	if (e->keys.updated <= 0)
		return ;
	e->keys.updated = 0;
	if (e->out.data == NULL)
		init_output(&e->out, &e->argn, &e->prim_map);
	size = e->out.size.x * e->out.size.y;
	ftocl_clear_current_kernel_arg(5);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 5, sizeof(t_camera),
		(void*)&e->cam);
	ftocl_run_percent_callback(size, 9, (void (*)(int, void *))percent_callback,
		e);
	ftocl_read_current_kernel_arg(0, e->out.data);
	ftocl_read_current_kernel_arg(1, e->prim_map.data);
	ftx_put_ubmp_img(ftx_data()->focused_window->vbuffer, ft_point(0, 0),
		&e->out, NOMASK);
	ftx_refresh_window(ftx_data()->focused_window);
}
