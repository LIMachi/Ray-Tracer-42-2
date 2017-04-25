/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_new_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 17:42:33 by hmartzol          #+#    #+#             */
/*   Updated: 2017/04/15 14:15:27 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftjson.h>
#include <libft.h>

inline static void			sf_jump_space(const char *src,
								const unsigned long length, unsigned long *pos)
{
	while (ft_isspace(src[*pos]) && *pos < length)
		++*pos;
}

inline static t_json_array	*sf_json_new_array(const char *src,
		const unsigned long length, unsigned long *pos, t_json_value *out)
{
	t_json_array	*ar;
	unsigned long	i;

	if ((ar = (t_json_array*)ft_memalloc(sizeof(t_json_array))) == NULL)
		return (NULL);
	ar->nb_values = ft_json_evaluate_array_size(src, length, (*pos)++);
	if (ar->nb_values < 1)
		return (ar);
	if ((ar->value = (t_json_value**)ft_memalloc(sizeof(t_json_value*) *
			ar->nb_values)) == NULL)
		return (ft_json_free_array(&ar));
	i = 0;
	while (i < ar->nb_values)
	{
		ar->value[i++] = ft_json_new_value(src, length, pos, out);
		sf_jump_space(src, length, pos);
		if (i < ar->nb_values)
		{
			if (src[*pos] == ',' && *pos < length)
				++*pos;
			else
				return (ft_json_free_array(&ar));
		}
	}
	return (ar);
}

t_json_value				*ft_json_new_array(const char *src,
		const unsigned long length, unsigned long *pos, t_json_value *parent)
{
	t_json_value	*out;

	if (*pos >= length || src == NULL || src[*pos] != '[' ||
			(out = ft_json_pack_value(parent, array, NULL)) == NULL)
		return (NULL);
	out->error =
	((out->ptr = (void*)sf_json_new_array(src, length, pos, out)) == NULL);
	sf_jump_space(src, length, pos);
	if (src[*pos] == ']' && *pos < length)
		++*pos;
	else
		out->error = 1;
	return (out);
}
