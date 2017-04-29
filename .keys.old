/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 06:57:34 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/13 06:57:35 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>


static int	e_move(int key, t_camera *cam)
{
	const int	dir[] = {
		-1, 1, -1, 1, -1, 1};
	const int	keys[] = {
		KEY_SHIFT_LEFT, KEY_SPACE, KEY_A, KEY_D, KEY_S, KEY_W};
	const int	v[] = {
		1, 1, 2, 2, 3, 3};
	cl_float4	vects[4];
	int			i;

	vects[1] = cam->up;
	vects[2] = cam->right;
	vects[3] = cam->dir;
	i = 0;
	while (i < 6)
	{
		if (keys[i] == key)
			cl_float4_p_add(&cam->pos, cl_float4_scale(vects[v[i]],
				10 * (dir[i] < 0 ? -1 : 1)));
		i++;
	}
	return (0);
}

static int	e_rotate(int key, t_camera *cam)
{
	const int	dir[] = {
		-1, 1, -1, 1, -1, 1};
	const int	keys[] = {
		KEY_LEFT, KEY_RIGHT, KEY_UP, KEY_DOWN, KEY_Q, KEY_E};
	const int	v[] = {
		1, 1, 2, 2, 3, 3};
	t_vector	vects[4];
	int			i;

	vects[1] = cam->origin_up;
	vects[2] = cam->origin_right;
	vects[3] = cam->origin_dir;
	i = 0;
	while (i < 6)
	{
		if (keys[i] == key)
			rotate_cam(cam, 0.05 * (double)dir[i], vects[v[i]]);
		i++;
	}
	return (0);
}

static int	e_save(int key, t_keys *keys)
{
	if (key == KEY_CTRL_LEFT)
		keys->ctrl = !keys->ctrl;
	if (key == KEY_S && keys->ctrl)
		ftx_screenshoot(ftx_data()->focused_window, NULL);
	return (0);
}

static int	cb_exit(int k, t_cmd *cmd)
{
	if (k == KEY_EXIT)
		ft_end(0);
	if (k == KEY_P)
		cmd->progress_bar_toggle ^= 1;
	return (0);
}

int			keys(t_env *e)
{
	ftx_set_key(KEY_SHIFT_LEFT, FTX_KEY_HOLD, (t_ftx_key)e_move, &e->cam);
	ftx_set_key(KEY_SPACE, FTX_KEY_HOLD, (t_ftx_key)e_move, &e->cam);
	ftx_set_key(KEY_D, FTX_KEY_HOLD, (t_ftx_key)e_move, &e->cam);
	ftx_set_key(KEY_A, FTX_KEY_HOLD, (t_ftx_key)e_move, &e->cam);
	ftx_set_key(KEY_W, FTX_KEY_HOLD, (t_ftx_key)e_move, &e->cam);
	ftx_set_key(KEY_S, FTX_KEY_HOLD, (t_ftx_key)e_move, &e->cam);
	ftx_set_key(KEY_LEFT, FTX_KEY_HOLD, (t_ftx_key)e_rotate, &e->cam);
	ftx_set_key(KEY_RIGHT, FTX_KEY_HOLD, (t_ftx_key)e_rotate, &e->cam);
	ftx_set_key(KEY_UP, FTX_KEY_HOLD, (t_ftx_key)e_rotate, &e->cam);
	ftx_set_key(KEY_DOWN, FTX_KEY_HOLD, (t_ftx_key)e_rotate, &e->cam);
	ftx_set_key(KEY_Q, FTX_KEY_HOLD, (t_ftx_key)e_rotate, &e->cam);
	ftx_set_key(KEY_E, FTX_KEY_HOLD, (t_ftx_key)e_rotate, &e->cam);
	ftx_set_key(KEY_CTRL_LEFT, FTX_KEY_HOLD, (t_ftx_key)e_save, &e);
	ftx_set_key(KEY_CTRL_LEFT, FTX_KEY_STATUS_RELEASED, (t_ftx_key)e_save, &e);
	ftx_set_key(KEY_S, FTX_KEY_STATUS_PRESSED, (t_ftx_key)e_save, &e->cam);
	ftx_set_key(KEY_EXIT, FTX_KEY_STATUS_PRESSED, (t_ftx_key)cb_exit, &e->cmd);
	ftx_set_key(KEY_P, FTX_KEY_HOLD, (t_ftx_key)cb_exit, &e->cmd);
	return (0);
}
