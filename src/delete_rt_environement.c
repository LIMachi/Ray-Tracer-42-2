/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_rt_environement.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/14 10:42:57 by hmartzol          #+#    #+#             */
/*   Updated: 2017/04/14 15:17:21 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void				delete_args(t_cl_kernel *ker)
{
	int		i;

	i = 0;
	while (i < ker->p_count)
	{
		if (ker->params[i].flags & (PARAM_CPY | PARAM_BUFFER) &&
			ker->params[i].mem)
			clReleaseMemObject(ker->params[i].mem);
		i++;
	}
	ft_memdel((void **)&ker->params);
}

void				delete_rt_environement(t_env *e)
{
	int	i;

	i = 0;
	while (i < e->argn.nb_materials)
		ft_memdel((void**)&e->materials.name[i++]);
	ft_memdel((void**)&e->materials.name);
	ft_memdel((void**)&e->materials.materials);
	i = 0;
	while (i < e->textures.nb_info)
		ft_memdel((void**)&e->textures.path[i++]);
	ft_memdel((void**)&e->textures.info);
	ft_memdel((void**)&e->textures.raw_bmp);
	ft_memdel((void**)&e->lights);
	ft_memdel((void**)&e->prim);
	ft_memdel((void**)&e->cmd.scene);
	ft_bzero(&e->argn, sizeof(t_argn));
	ft_bzero(&e->textures, sizeof(t_textures_holder));
	ft_bzero(&e->materials, sizeof(t_material_holder));
	delete_args(e->glfw.render);
}
