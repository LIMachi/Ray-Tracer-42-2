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

void		rotate_cam(t_camera *cam, double angle, t_vector axe)
{
	t_vector		t[3];
	t_quaternion	q;
	t_matrix		*mat;
	t_vector		*r;

	q = ft_quat_rotation_build(angle, axe);
	printf("%f %f %f %f\n", q.r, q.i, q.j, q.k);
	q = ft_quat_multiply(cam->orientation, q);
	printf("%f %f %f %f\n", q.r, q.i, q.j, q.k);
	cam->orientation = q;
	mat = ft_quat_rotation_to_matrix(NULL, q);
	t[0] = cam->origin_dir;
	t[1] = cam->origin_up;
	t[2] = cam->origin_right;
	printf("%f dir : %f %f %f\n", angle, t[0].x, t[0].y, t[0].z);
	printf("%f dir : %f %f %f\n", angle, t[1].x, t[1].y, t[1].z);
	printf("%f dir : %f %f %f\n", angle, t[2].x, t[2].y, t[2].z);
	r = ft_matrix_multply_vector_array(t, 3, mat);
	printf("dir : %f %f %f\n", t[0].x, t[0].y, t[0].z);
	printf("dir : %f %f %f\n", t[1].x, t[1].y, t[1].z);
	printf("dir : %f %f %f\n", t[2].x, t[2].y, t[2].z);
	cam->dir = vector_to_cl_float4(t[0]);
	cam->up = vector_to_cl_float4(t[1]);
	cam->right = vector_to_cl_float4(t[2]);
	ft_matrix_free(mat);
	calc_vpul(cam);
}
