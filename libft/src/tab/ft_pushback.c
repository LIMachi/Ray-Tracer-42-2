/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushback.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/17 07:30:52 by cchaumar          #+#    #+#             */
/*   Updated: 2017/02/17 07:30:54 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_pushback(void **data, size_t size, int count, void *o)
{
	unsigned char	*p;
	unsigned char	*u;
	size_t			i;

	p = ft_malloc(size * (count + 1));
	u = (unsigned char *)*data;
	i = 0;
	while (i < (count * size))
	{
		p[i] = u[i];
		i++;
	}
	u = (unsigned char *)o;
	while (i < (count + 1) * size)
	{
		p[i] = u[i - count * size];
		i++;
	}
	free(*data);
	*data = p;
}
