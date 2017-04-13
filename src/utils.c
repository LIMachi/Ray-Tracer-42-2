/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 23:18:37 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/13 23:18:38 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void	die(int err, char *msg, const char *err_log, ...)
{
	va_list	va;

	va_start(va, err_log);
	if (err_log)
		ft_vadprintf(2, err_log, va);
	ft_error(err, msg);
}
