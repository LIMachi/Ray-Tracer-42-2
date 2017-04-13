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

void		percent_callback(int percent, void *data)
{
	int y;
	int chunk;

	(void)data;
	if (cmd()->progress_bar_toggle)
	{
		y = 0;
		chunk = (int)(argn()->screen_size.x / 100);
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

void		update(t_env *e, int u)
{
	size_t size;

	if (u <= 0)
		return ;
	if (out()->data == NULL)
		init_output();
	size = out()->size.x * out()->size.y;
	ftocl_clear_current_kernel_arg(5);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 5, sizeof(t_camera),
			(void*)cam());
	ftocl_run_percent_callback(size, 9, percent_callback, NULL);
	ftocl_read_current_kernel_arg(0, out()->data);
	ftocl_read_current_kernel_arg(1, prim_map()->data);
	ftx_put_ubmp_img(ftx_data()->focused_window->vbuffer, ft_point(0, 0), out(),
		NOMASK);
	ftx_refresh_window(ftx_data()->focused_window);
}
