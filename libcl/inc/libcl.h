/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/13 09:47:54 by cchaumar          #+#    #+#             */
/*   Updated: 2017/04/13 09:49:30 by cchaumar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCL_H
# define LIBCL_H

# include <libft.h>

# if OS == LINUX
#  include <CL/opencl.h>
# elif OS == MACINTOCH
#  include <OpenCL/opencl.h>
# else
#  error "unsuported os"
# endif

#endif
