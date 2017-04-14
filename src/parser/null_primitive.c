/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_primitive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 08:13:55 by hmartzol          #+#    #+#             */
/*   Updated: 2017/04/14 08:21:07 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_primitive	null_primitive(void)
{
	return ((t_primitive){.type = INVALID, .position = {.v4 = {0, 0, 0, 0}},
		.direction = {.v4 = {0, 0, 0, 0}}, .radius = 0, .material = 0,
		.limit = {.relative = 0, .high = {.v4 = {0, 0, 0, 0}},
		.low = {.v4 = {0, 0, 0, 0}}}});
}
