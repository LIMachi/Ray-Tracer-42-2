/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsed_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 02:03:32 by hmartzol          #+#    #+#             */
/*   Updated: 2017/04/13 05:48:29 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
/*
inline static int	check_null_cl_float4(cl_float4 v)
{
	return (v.x == 0 && v.y == 0 && v.z == 0 && v.w == 0);
}
*/
int					check_parsed_data(const t_argn *argn, const t_camera *cam)
{
	(void)argn;
	(void)cam;
/*	if (argn->screen_size.x <= 0 || argn->screen_size.y <= 0 ||
			check_null_cl_float4(cam->dir) || check_null_cl_float4(cam->up) ||
			check_null_cl_float4(cam->right) || cam->vp_size.x <= 0 ||
			cam->vp_size.y <= 0 || cam->dist <= 0)
		return (0);*/
	return (1);
}
