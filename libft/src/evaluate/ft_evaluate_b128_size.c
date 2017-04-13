/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_evaluate_b128_size.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lee <lee@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 18:23:23 by lee               #+#    #+#             */
/*   Updated: 2017/03/17 05:26:05 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_evaluate_b128_size(__uint128_t v)
{
	size_t	l;

	if (v == 0)
		return (1);
	l = 1;
	while (v >>= 1)
		++l;
	return (l);
}
