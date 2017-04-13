/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_key_hook.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 12:56:42 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/21 17:18:45 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

int	ftx_set_key(int key, int state, t_ftx_key cb)
{
	t_key_data	*data;

	if (key >= KEYMAP_SIZE)
	{
		ft_error(EINVAL, "ftx_set_key got wrong key code\n");
		return (-1);	
	}
	data = ftx_data()->keymap;
	if (state == FTX_KEY_STATUS_PRESSED)
		data[key].press = cb;
	else if (state == FTX_KEY_STATUS_HOLD)
		data[key].hold = cb;
	else if (state == FTX_KEY_STATUS_RELEASED)
		data[key].release = cb;
	return (0);
}
