/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmerge.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/22 02:49:49 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/22 02:50:26 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmerge(char *a, char *b)
{
	char	*ret;

	ret = ft_strjoin(a, b);
	ft_strdel(&a);
	ft_strdel(&b);
	return (ret);
}

char	*ft_strmergeflag(char *a, char *b, int flag)
{
	char	*ret;

	ret = ft_strjoin(a, b);
	if (flag & 1)
		ft_strdel(&a);
	if (flag & 2)
		ft_strdel(&b);
	return (ret);
}
