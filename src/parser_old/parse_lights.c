/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 02:05:29 by hmartzol          #+#    #+#             */
/*   Updated: 2017/04/14 14:51:00 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

inline static cl_float4	cl_vector_from_json_array0(t_json_value *node,
											cl_float4 default_return)
{
	t_json_value		**ar;
	cl_float4			out;
	t_json_value_type	*la_norm_me_troll;

	la_norm_me_troll = (t_json_value_type[4])
		{integer | number, integer | number, integer | number, boolean};
	if (!ft_json_check_array_types(node, 4, la_norm_me_troll))
		return (default_return);
	ar = ((t_json_array*)node->ptr)->value;
	out.x = ar[0]->type == integer ?
		(cl_float) * (int*)ar[0]->ptr : (cl_float) * (double*)ar[0]->ptr;
	out.y = ar[1]->type == integer ?
		(cl_float) * (int*)ar[1]->ptr : (cl_float) * (double*)ar[1]->ptr;
	out.z = ar[2]->type == integer ?
		(cl_float) * (int*)ar[2]->ptr : (cl_float) * (double*)ar[2]->ptr;
	out.w = (cl_float) * (int*)ar[3]->ptr;
	return (out);
}

void					parse_lights(t_json_value *l, t_argn *argn,
	t_light **lights)
{
	t_json_array	*ar;
	unsigned long	i;

	if (l == NULL || l->type != array || (ar = (t_json_array*)l->ptr) == NULL ||
		(argn->nb_lights = ar->nb_values) == 0 || ar->value == NULL ||
		(*lights = (t_light*)ft_malloc(sizeof(t_light) * ar->nb_values))
		== NULL)
		return ;
	i = -1;
	while (++i < ar->nb_values)
		(*lights)[i] = (t_light){.position =
		cl_vector_from_json_array0(ft_json_search_pair_in_object(ar->value[i],
		(t_json_string){.length = 8, .ptr = "position"}),
		(cl_float4){.x = 0, .y = 0, .z = 0, .w = 0}), .color =
		cl_vector_from_json_array(ft_json_search_pair_in_object(ar->value[i],
		(t_json_string){.length = 5, .ptr = "color"}),
		(cl_float4){.x = 1, .y = 1, .z = 1, .w = 0})};
}
