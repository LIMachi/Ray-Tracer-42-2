#include <libftjson.h>
#include <stdlib.h>

t_json_value	*ft_json_search_index_in_array(t_json_value *value,
												unsigned long index)
{
	t_json_array	*ar;

	if (!ft_json_test_type(value, array))
		return (NULL);
	ar = (t_json_array*)value->ptr;
	if (index >= ar->nb_values)
		return (NULL);
	return (ar->value[index]);
}
