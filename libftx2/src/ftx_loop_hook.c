/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftx_loop_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/07 19:30:22 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/07 19:55:25 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftx.h>

int	ftx_loop_hook(t_ftx_loop_cb cb, void *user_data, int *updated)
{
	t_ftx_data	*data;

	data = ftx_data();
	if (data == NULL)
		return (-1);
	if (data->loop_callback != NULL)
		return (1);
	data->loop_callback = cb;
	data->user_data = user_data;
	data->updated = updated;
	return (0);
}
