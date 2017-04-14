/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 14:37:45 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/27 08:43:44 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <stdio.h>

void		calc_vpul(t_camera *cam)
{
	float	y;
	float	x;

	y = ((float)cam->vp_size.y / 2.0f);
	x = -((float)cam->vp_size.x / 2.0f);
	cam->vpul.x = ((cam->dir.x * cam->dist) +
			(cam->up.x * y)) + (cam->right.x * x);
	cam->vpul.y = ((cam->dir.y * cam->dist) +
			(cam->up.y * y)) + (cam->right.y * x);
	cam->vpul.z = ((cam->dir.z * cam->dist) +
			(cam->up.z * y)) + (cam->right.z * x);
	cam->vpul.w = 0.0f;
}

t_vector	cl_float4_to_vector(cl_float4 v)
{
	return ((t_vector){.x = v.x, .y = v.y, .z = v.z});
}

cl_float4	vector_to_cl_float4(t_vector v)
{
	return ((cl_float4){.x = v.x, .y = v.y, .z = v.z, .w = 0.0f});
}
