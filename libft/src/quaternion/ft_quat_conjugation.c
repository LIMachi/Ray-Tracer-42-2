/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quat_conjugation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 04:01:41 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/13 04:01:59 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_quat_conjugation(const t_quaternion q, t_vector *v)
{
	t_quaternion	p;
	
	p = ft_quat(0, v->x, v->y, v->z);
	p = ft_quat_multiply(p, ft_quat_inverse(q));
	p = ft_quat_multiply(q, p);
	*v = (t_vector){p.i, p.j, p.k};
}
