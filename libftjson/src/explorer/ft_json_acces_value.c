#include <stdarg.h>
#include <libftjson.h>
#include <stdlib.h>

t_json_value	*ft_json_acces_value(const t_json_value *root, int *error,
									char *form, ...)
{
	va_list			ap;
	t_json_value	*tmp;

	error = (error == NULL) ? (int*)(int[1]){0} : error;
	if (form == NULL && (*error = 1))
		return (NULL);
	tmp = (t_json_value *)root;
	va_start(ap, form);
	--form;
	while (*++form != '\0' && tmp != NULL)
		if (*form == 'a')
			tmp = ft_json_search_index_in_array(tmp, va_arg(ap, unsigned long));
		else if (*form == 'o')
			tmp = ft_json_search_pair_in_object(tmp, ft_json_s_string(
				va_arg(ap, char *)));
		else
			tmp = NULL;
	va_end(ap);
	*error &= (tmp == NULL);
	return (tmp);
}
