/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 09:37:48 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/07 19:54:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <mlx.h>
#include <libftx.h>

#if 0

static int	sf_tick(void *data)
{
	t_key_data	*keymap;
	int			i;

	++((t_ftx_data*)data)->tick;
	keymap = ((t_ftx_data*)data)->keymap;
	i = -1;
	while (++i < KEYMAP_SIZE)
		if (keymap[i].callback != NULL)
			keymap[i].callback(i, keymap[i].status, keymap[i].data);
	return (((t_ftx_data*)data)->tick);
}

#else

static int	sf_run_keys(t_key_data *pkey)
{
	int		i;
	int		u;

	i = 0;
	u = 0;
	while (i < KEYMAP_SIZE)
	{
		if (pkey->status == FTX_KEY_STATUS_HOLD && pkey->hold && ++u)
			pkey->hold(i, pkey->data[FTX_KEY_STATUS_HOLD]);
		pkey++;
		i++;
	}
	return (u);
}

static int	sf_tick(t_ftx_data *data)
{
	int		u;

	++data->tick;
	u = sf_run_keys(data->keymap);
	if (data->updated)
		*data->updated = u;
	if (data->loop_callback != NULL)
		data->loop_callback(data->user_data);
	return (data->tick);
}

#endif

static void	sf_end(void)
{
	if (ftx_data() == NULL || ftx_data()->mlx)
		return ;
	mlx_do_key_autorepeaton(ftx_data()->mlx);
}

void		ftx_start(void)
{
	t_ftx_data	*data;

	if ((data = ftx_data())->mlx == NULL)
		return ;
	ft_atend(&sf_end);
	mlx_do_key_autorepeatoff(data->mlx);
	mlx_loop_hook(data->mlx, (int (*)(void *))sf_tick, (void*)data);
	mlx_loop(data->mlx);
}
