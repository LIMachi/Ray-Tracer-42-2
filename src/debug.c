/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 17:59:00 by hmartzol          #+#    #+#             */
/*   Updated: 2017/05/10 07:28:17 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>
#include <stdio.h>

void		print_cl_float4(cl_float4 v)
{
	printf("{%f, %f, %f, %f}", v.x, v.y, v.z, v.w);
}

void		print_cl_float2(cl_float2 v)
{
	printf("{%f, %f}", v.x, v.y);
}

void		print_cl_int2(cl_int2 v)
{
	printf("{%d, %d}", v.x, v.y);
}

void		debug(t_env *e)
{
	printf("\n\ndebuging environement structure at address: %p\n{\n", e);
	printf("lights = %p\nprim = %p\n", e->lights, e->prim);
	printf("materials = {\n\tnb_metrials = %d", e->materials.nb_materials);
	for (int i = 0; i < e->materials.nb_materials; ++i)
	{
		printf("\n\t\tname = \"%s\"\n", e->materials.name[i]);
		printf("\t\tcolor = "); print_cl_float4(e->materials.materials[i].color);
		printf("\n\t\tdiffuse = "); print_cl_float4(e->materials.materials[i].diffuse);
		printf("\n\t\tspecular = "); print_cl_float4(e->materials.materials[i].specular);
		printf("\n\t\treflection = %f\n", e->materials.materials[i].reflection);
		printf("\t\trefraction = %f\n", e->materials.materials[i].refraction);
		printf("\t\tbrightness = %f\n", e->materials.materials[i].brightness);
		printf("\t\tperturbation = \n\t\t{\n\t\t\tnormal = %f, color = '%s'}\n", e->materials.materials[i].perturbation.normal, _PERTURBATIONS[e->materials.materials[i].perturbation.color]);
		printf("\t\ttexture = \n\t\t{\n\t\t\tinfo_index = %llu\n", e->materials.materials[i].texture.info_index);
		printf("\t\t\tstretch = "); print_cl_float2(e->materials.materials[i].texture.stretch);
		printf("\n\t\t\toffset = "); print_cl_float2(e->materials.materials[i].texture.offset);
		printf("\n\t\t}\n\t\tnormal_map = \n\t\t{\n\t\t\tinfo_index = %llu\n", e->materials.materials[i].normal_map.info_index);
		printf("\t\t\tstretch = "); print_cl_float2(e->materials.materials[i].normal_map.stretch);
		printf("\n\t\t\toffset = "); print_cl_float2(e->materials.materials[i].normal_map.offset);
		printf("\n\t\t}\n");
	}
	printf("\t}\n\ttextures = \n\t{\n\t\tnb_info = %d", e->textures.nb_info);
	for (int i = 0; i < e->textures.nb_info; ++i)
	{
		printf("\n\t\tpath = \"%s\"\n", e->textures.path[i]);
		printf("\t\tinfo = \n\t\t{\n\t\t\tindex = %llu\n", e->textures.info[i].index);
		printf("\t\t\tsize = "); print_cl_int2(e->textures.info[i].size);
		printf("\n\t\t}\n");
	}
	printf("\t\ttotal_raw_size = %d\n", e->textures.total_raw_size);
	printf("\t\traw_bmp = %p\n\t}\n", e->textures.raw_bmp);
	printf("argn = \n{\n\tscreen_size = "); print_cl_int2(e->argn.screen_size);
	printf("\n\tnb_onjects = %d\n", e->argn.nb_objects);
	printf("\tnb_lights = %d\n", e->argn.nb_lights);
	printf("\tmap_primitives = %d\n", e->argn.map_primitives);
	printf("\tambient = %f\n", e->argn.ambient);
	printf("\tdirect = %f\n", e->argn.direct);
	printf("\tantialias = %d\n", e->argn.antialias);
	printf("\tbounce_depth = %d\n", e->argn.bounce_depth);
	printf("\tfilter = '%s'\n", _FILTERS[e->argn.filter]);
	printf("\tstereoscopy = %d\n", e->argn.stereoscopy);
	printf("\tskybox = \n\t{\n\t\tinfo_index = %llu\n", e->argn.skybox.info_index);
	printf("\t\tstretch = "); print_cl_float2(e->argn.skybox.stretch);
	printf("\n\t\toffset = "); print_cl_float2(e->argn.skybox.offset);
	printf("\n\t}\n\tnb_info = %d\n", e->argn.nb_info);
	printf("\tnb_materials = %d\n", e->argn.nb_materials);
	printf("\tmoving = %d\n}\n", e->argn.moving);
	printf("cam =\n{\n\tpos = "); print_cl_float4(e->cam.pos);
	printf("\n\tdir = "); print_cl_float4(e->cam.dir);
	printf("\n\tup = "); print_cl_float4(e->cam.up);
	printf("\n\tright = "); print_cl_float4(e->cam.right);
	printf("\n\tvpul = "); print_cl_float4(e->cam.vpul);
	printf("\n\tvp_size = "); print_cl_float2(e->cam.vp_size);
	printf("\n\tspeed = %f\n", e->cam.speed);
	printf("\tdist = %f\n", e->cam.dist);
	printf("\torientation = {%f, %f, %f, %f}\n", e->cam.orientation.r, e->cam.orientation.i, e->cam.orientation.j, e->cam.orientation.k);
	printf("\torigin_dir = {%f, %f, %f}\n", e->cam.origin_dir.x, e->cam.origin_dir.y, e->cam.origin_dir.z);
	printf("\torigin_up = {%f, %f, %f}\n", e->cam.origin_up.x, e->cam.origin_up.y, e->cam.origin_up.z);
	printf("\torigin_right = {%f, %f, %f}\n}\n", e->cam.origin_right.x, e->cam.origin_right.y, e->cam.origin_right.z);
	printf("lights = \n{");
	for (int i = 0; i < e->argn.nb_lights; ++i)
	{
		printf("\n\tposition = "); print_cl_float4(e->lights[i].position);
		printf("\n\tcolor = "); print_cl_float4(e->lights[i].color);
		printf("\n");
	}
	printf("}\nprim =\n{");
	for (int i = 0; i < e->argn.nb_objects; ++i)
	{
		printf("\n\ttype = '%s'\n", _TYPES[e->prim[i].type]);
		printf("\tposition = "); print_cl_float4(e->prim[i].position);
		printf("\n\tdirection = "); print_cl_float4(e->prim[i].direction);
		printf("\n\tradius = %f\n", e->prim[i].radius);
		printf("\tmaterial = %d\n", e->prim[i].material);
		printf("\tlimit =\n\t{\n\t\trelative = '%s'\n", _BOOLEAN[e->prim[i].limit.relative]);
		printf("\t\thigh = "); print_cl_float4(e->prim[i].limit.high);
		printf("\n\t\tlow = "); print_cl_float4(e->prim[i].limit.low);
		printf("\n\t\trotation = "); print_cl_float4(e->prim[i].limit.rotation);
		printf("\n\t}\n\tgroup_id = %d\n", e->prim[i].group_id);
	}
	printf("}\nnb_groups = %d\ngroup =\n{", e->nb_groups);
	for (unsigned i = 0; i < e->nb_groups; ++i)
	{
		printf("\n\tnb_prims = %d\n\tprim_ids =\n\t[\n", e->group[i].nb_prims);
		for (unsigned j = 0; j < e->group[i].nb_prims; ++j)
			printf("\t\t%d\n", e->group[i].prim_ids[j]);
		printf("\t]\n");
	}
	printf("}\n");
	ft_end(0);
}
