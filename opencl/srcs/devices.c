/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   devices.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/04 11:22:34 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/11 16:58:07 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_opencl.h"

static void		add_devices(cl_device_id **t, int *n, cl_platform_id id,
	int type)
{
	cl_device_id	*dev;
	cl_uint			dn;
	cl_uint			i;

	clGetDeviceIDs(id, type, 0, 0, &dn);
	if (!dn)
		return ;
	dev = try(sizeof(cl_device_id) * dn);
	clGetDeviceIDs(id, type, dn, dev, 0);
	i = 0;
	while (i < dn)
		ft_pushback((void **)t, sizeof(cl_device_id), (*n)++, dev + (i++));
	free(dev);
}

cl_device_id	select_device(int type)
{
	cl_device_id	*t;
	cl_platform_id	*p;
	cl_uint			pn;
	cl_uint			i;
	int				n;

	t = NULL;
	n = 0;
	clGetPlatformIDs(0, NULL, &pn);
	p = try(sizeof(cl_platform_id) * pn);
	clGetPlatformIDs(pn, p, NULL);
	i = 0;
	while (i < pn)
		add_devices(&t, &n, p[i++], type);
	return (t[0]);
}
