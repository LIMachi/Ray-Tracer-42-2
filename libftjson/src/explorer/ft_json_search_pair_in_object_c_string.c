#include <libftjson.h>
#include <libft.h>

t_json_value	*ft_json_search_pair_in_object_c_string(t_json_value *v,
					const char *str)
{
	unsigned long	i;
	t_json_object	*obj;

	if (!ft_json_test_type(v, object))
		return (NULL);
	obj = (t_json_object*)v->ptr;
	i = -1;
	while (++i < obj->nb_pairs)
		if (obj->pair[i] != NULL && obj->pair[i]->key != NULL &&
				obj->pair[i]->key->ptr != NULL &&
				ft_strcmp(obj->pair[i]->key->ptr, (char*)str) == 0)
			return (obj->pair[i]->value);
	return (NULL);
}
