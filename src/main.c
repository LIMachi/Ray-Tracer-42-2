/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 09:15:54 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/25 23:47:50 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include "mlx.h"

void		rt(t_env *e)
{
	calc_vpul(&e->cam);
	update_kernel_args(e);
	if (e->cmd.output != NULL)
		direct_output(&e->out, &e->argn, e->cmd.output);
	ftx_new_window(ft_point(e->argn.screen_size.x, e->argn.screen_size.y),
		"RT", NULL);
	keys(e);
	e->keys.updated = 1;
	update(e);
	ftx_loop_hook((t_ftx_loop_cb)update, e, &e->keys.updated);
	mlx_hook(ftx_data()->focused_window->win, 4, 1, mouse_click, e);
	mlx_hook(ftx_data()->focused_window->win, 5, 1, mouse_off, e);
	mlx_hook(ftx_data()->focused_window->win, 6, 1, mouse_move, e);
	ftx_start();
}

void		init(t_env *e, char *src)
{
	int		fd;

	if ((fd = open(e->cmd.scene, O_RDONLY)) == -1)
		ft_end(-1);
	e->cam.orientation.r = 1;
	parser(e, src = ft_readfile(fd));
	close(fd);
	ft_free(src);
	if ((fd = open(OCL_SOURCE_PATH, O_RDONLY)) == -1)
		ft_end(-1);
	ftocl_make_program(ft_str_to_id64("rt"),
			src = ft_str_clear_commentaries(ft_readfile(fd)), NULL);
	close(fd);	
}

int			main(const int argc, char **argv, char **env)
{
	t_env	e;
	int		fd;
	char	*src;

	ft_bzero(&e, sizeof(t_env));
	ft_init(env);
	if (command_line(&e.cmd, argc, argv))
	{
		ft_printf("\nUsage: \t%s/%s <scene.json>\n\n", ft_pwd(),
		ft_path_name(argv[0]));
		ft_end(0);
	}
	init(&e, src);
	if (!(fd = ftocl_set_current_kernel(ft_str_to_id64("rt_kernel"))))
		rt(&e);
	ft_free(src);
	if (fd == 1)
		ft_end(0 /* ft_printf("kernel was not found\n")*/);
	ft_end(0);
}
