/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 14:39:36 by hmartzol          #+#    #+#             */
/*   Updated: 2017/02/07 00:59:55 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_putstr_fd(char const *s, int fd)
{
	if (s == NULL)
		return ;
	ft_void(write(fd, s, ft_strlen(s)));
	if ((*ft_global_flags() & GF_FORCE_LOG) == GF_FORCE_LOG)
		ft_global_log(LOG_SET | LOG_STORE, (char*)s);
}
