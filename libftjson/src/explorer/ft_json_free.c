/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_json_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 18:30:05 by hmartzol          #+#    #+#             */
/*   Updated: 2017/01/27 07:55:40 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftjson.h>
#include <libft.h>

void	*ft_json_free_pair(t_json_pair **pair)
{
	if (pair == NULL || *pair == NULL)
		return (NULL);
	ft_json_free_string(&(*pair)->key);
	ft_json_free_value(&(*pair)->value);
	ft_free(*pair);
	return (*pair = NULL);
}

void	*ft_json_free_object(t_json_object **object)
{
	unsigned long	i;

	if (object == NULL || *object == NULL)
		return (NULL);
	i = 0;
	if ((*object)->pair != NULL)
	{
		while (i < (*object)->nb_pairs)
			ft_json_free_pair(&(*object)->pair[i]);
		(*object)->nb_pairs = 0;
		ft_free((*object)->pair);
		(*object)->pair = NULL;
	}
	ft_free(*object);
	return (*object = NULL);
}

void	*ft_json_free_array(t_json_array **array)
{
	unsigned long	i;

	if (array == NULL || *array == NULL)
		return (NULL);
	i = 0;
	if ((*array)->value != NULL)
	{
		while (i < (*array)->nb_values)
			ft_json_free_value(&(*array)->value[i]);
		ft_free((*array)->value);
		(*array)->value = NULL;
	}
	ft_free(*array);
	return (*array = NULL);
}

void	*ft_json_free_string(t_json_string **string)
{
	if (string == NULL || *string == NULL)
		return (NULL);
	(*string)->length = 0;
	if ((*string)->ptr != NULL)
	{
		ft_free((*string)->ptr);
		(*string)->ptr = NULL;
	}
	ft_free(*string);
	return (*string = NULL);
}

void	*ft_json_free_value(t_json_value **node)
{
	if (node == NULL || *node == NULL)
		return (NULL);
	if ((*node)->type == object)
		ft_json_free_object((t_json_object**)&(*node)->ptr);
	if ((*node)->type == array)
		ft_json_free_array((t_json_array**)&(*node)->ptr);
	if ((*node)->type == string)
		ft_json_free_string((t_json_string**)&(*node)->ptr);
	if ((*node)->type == null || (*node)->type == boolean ||
			(*node)->type == integer || (*node)->type == number)
		if ((*node)->ptr != NULL)
			ft_free((*node)->ptr);
	(*node)->parent = NULL;
	(*node)->type = invalid;
	(*node)->ptr = NULL;
	ft_free(*node);
	return (*node = NULL);
}
