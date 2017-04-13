/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_kernel_args.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 14:38:52 by hmartzol          #+#    #+#             */
/*   Updated: 2017/04/13 06:35:13 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <stdio.h>

inline static void	update_kernel_args_0(t_env *e)
{
	ftocl_clear_current_kernel_arg(6);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 6, sizeof(t_img_info) *
		e->argn.nb_info + 1, (void*)e->textures_holder.info);
	ftocl_clear_current_kernel_arg(7);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 7, sizeof(t_material) *
		e->argn.nb_materials, (void*)e->materials.materials);
	ftocl_clear_current_kernel_arg(8);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 8, sizeof(cl_int) *
	e->textures_holder.total_raw_size + 1, (void*)e->textures_holder.raw_bmp);
}

void				update_kernel_args(t_env *e)
{
	ftocl_clear_current_kernel_arg(0);
	ftocl_set_current_kernel_arg(CL_MEM_WRITE_ONLY, 0, sizeof(cl_int) *
		e->argn.screen_size.x * e->argn.screen_size.y, NULL);
	ftocl_clear_current_kernel_arg(1);
	ftocl_set_current_kernel_arg(CL_MEM_WRITE_ONLY, 1, sizeof(cl_int) *
		e->argn.screen_size.x * e->argn.screen_size.y, NULL);
	e->argn.map_primitives = (e->cmd.output == NULL);
	ftocl_clear_current_kernel_arg(2);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 2, sizeof(t_argn),
		(void*)&e->argn);
	ftocl_clear_current_kernel_arg(3);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 3, sizeof(t_primitive) *
		e->argn.nb_objects, (void*)e->prim);
	ftocl_clear_current_kernel_arg(4);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 4, sizeof(t_light) *
		e->argn.nb_lights, (void*)e->lights);
	ftocl_clear_current_kernel_arg(5);
	ftocl_set_current_kernel_arg(CL_MEM_READ_ONLY, 5, sizeof(t_camera),
		(void*)&e->cam);
	update_kernel_args_0(e);
}
