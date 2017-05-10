/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   default_material.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 02:00:39 by hmartzol          #+#    #+#             */
/*   Updated: 2017/05/08 17:54:16 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

t_material			default_material(void)
{
	t_material	out;

	out.color = (cl_float4){.x = 1.0f, .y = 1.0f, .z = 1.0f, .w = 0.0f};
	out.diffuse = (cl_float4){.x = 0.4f, .y = 0.4f, .z = 0.4f, .w = 0.0f};
	out.specular = (cl_float4){.x = 0.5f, .y = 0.5f, .z = 0.5f, .w = 0.0f};
	out.reflection = 0.0f;
	out.refraction = 0.0f;
	out.perturbation.normal = 0.0f;
	out.perturbation.color = NONE;
	out.texture.info_index = -1;
	out.texture.stretch = (cl_float2){.x = 1.0f, .y = 1.0f};
	out.texture.offset = (cl_float2){.x = 0.0f, .y = 0.0f};
	out.normal_map.info_index = -1;
	out.normal_map.stretch = (cl_float2){.x = 1.0f, .y = 1.0f};
	out.normal_map.offset = (cl_float2){.x = 0.0f, .y = 0.0f};
	return (out);
}
