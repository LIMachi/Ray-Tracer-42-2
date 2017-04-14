/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbondoer <pbondoer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:14:54 by pbondoer          #+#    #+#             */
/*   Updated: 2017/04/14 12:10:22 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			command_line(t_cmd *cmd, int argc, char **argv)
{
	int i;

	i = 1;
	while (i < argc)
	{
		if (argv[i][0] == '-')
		{
			if (i + 1 >= argc)
				return (1);
			if (argv[i][1] == 'o')
				cmd->output = argv[i + 1];
			i++;
		}
		else
			cmd->scene = ft_strdup(argv[i]);
		i++;
	}
	if (cmd->scene == NULL)
		return (1);
	return (argc == 1);
}
