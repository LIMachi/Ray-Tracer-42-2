/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_groups.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/01 20:50:10 by hmartzol          #+#    #+#             */
/*   Updated: 2017/05/01 20:50:12 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <rt_parser.h>

t_group				group_constructor(t_group_constructor *gc, t_env *e,
										unsigned id)
{
	t_group		out;
	unsigned	i;
	t_primitive	old;
	t_primitive	*tmp;

	out.prim_ids = ft_memalloc(sizeof(int) * gc->nb_prims);
	out.nb_prims = gc->nb_prims;
	i = -1;
	old = e->prim[e->argn.nb_objects];
	while (++i < out.nb_prims)
	{
		tmp = &e->prim[e->argn.nb_objects++];
		*tmp = gc->prim[i];
		tmp->group_id = id;
		cl_float4_p_add(&tmp->position, old.position);
		if (tmp->material == null_primitive().material)
			tmp->material = old.material;
	}
	return (out);
}

void				load_group(t_json_value *o, t_env *e) //try to load a group
{
	unsigned long	i;
	t_json_value	*v;

	v = ft_json_search_pair_in_object_c_string(o, "type");
	if (!ft_json_test_type(v, string))
		return ;
	if (e->nb_group_constructors == 0)
		return ;
	i = 0;
	while (i < e->nb_group_constructors &&
			ft_strcmp((char*)v->ptr, e->group_constructor[i].name))
		++i;
	if (i == e->nb_group_constructors)
		return ;
	if (e->group_constructor[i].nb_prims == 0)
		return ;
	e->group[e->nb_groups] = group_constructor(&e->group_constructor[i], e, i);
}

inline static void	parse_group(t_json_array *ar, t_env *e,
								t_group_constructor *g)
{
	unsigned long	i;

	(void)e;
	g->nb_prims = ar->nb_values;
	g->prim = ft_memalloc(sizeof(t_primitive) * ar->nb_values);
	i = -1;
/*	while (++i < ar->nb_values)
		if (ft_json_test_type(ar->value[i], object))
			g->prim[i] = parse_object(ar->value[i], &e->materials, &e->textures);
		else
			g->prim[i] = null_primitive();
*/}

void				parse_groups(t_json_value *v, t_env *e)
{
	t_json_object	*obj;
	unsigned long	i;

	e->nb_group_constructors = 0;
	if (!ft_json_test_type(v, object))
		return ;
	if ((obj = (t_json_object*)v->ptr)->nb_pairs <= 0)
		return ;
	if ((e->group_constructor = ft_memalloc(sizeof(t_group_constructor) * obj->nb_pairs)) == NULL)
		return ;
	e->nb_group_constructors = obj->nb_pairs;
	i = -1;
	while (++i < obj->nb_pairs)
		if (obj->pair[i] != NULL)
		{
			e->group_constructor[i].name = obj->pair[i]->key->ptr;
			if (ft_json_test_type(obj->pair[i]->value, array))
				parse_group((t_json_array*)obj->pair[i]->value->ptr, e,
							&e->group_constructor[i]);
		}
		else
			e->group_constructor[i].nb_prims = 0;
}
