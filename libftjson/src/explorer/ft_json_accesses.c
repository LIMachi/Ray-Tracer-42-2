#include <stdarg.h>
#include <stdlib.h>
#include <libftjson.h>

inline static int	sf_json_accesses_access_right(t_jae *e, va_list ap)
{
	t_json_value	*tmp;
	int				tmp1;
	char			*tmp2;

	if (e->error_stack)
		++e->error_stack;
	else if ((e->etype != object && e->etype != array) ||
			!ft_json_test_type(e->node, e->etype))
		e->error_stack = 1;
	if (e->error_stack)
		return (1 | va_arg(ap, size_t));
	if (e->etype == object)
	{
		if ((tmp = ft_json_search_pair_in_object_c_string(e->node,
				tmp2 = va_arg(ap, char *))) == NULL)
			return (e->error_stack = 1);
		e->node = tmp;
		return (1);
	}
	if ((tmp = ft_json_search_index_in_array(e->node,
			tmp1 = va_arg(ap, int))) == NULL)
		return (e->error_stack = 1);
	e->node = tmp;
	return (1);
}

inline static void	sf_json_accesses_access_store(t_jae *e, void *tmp)
{
	if (e->node->type == string)
		*(char**)tmp = ((t_json_string*)e->node->ptr)->ptr;
	if (e->node->type & (null | array | object))
		*(void**)tmp = e->node->ptr;
	if (e->node->type == number)
		*(double*)tmp = *(double*)e->node->ptr;
	if (e->node->type == integer)
	{
		if ((e->etype & number) == number)
			*(double*)tmp = (double)*(int*)e->node->ptr;
		else
			*(int*)tmp = *(int*)e->node->ptr;
	}
	if (e->node->type == boolean)
		*(int*)tmp = *(int*)e->node->ptr;
	if (e->node->type == none)
		*(void**)tmp = e->node;
}

inline static void	sf_json_accesses_access_call(t_jae *e, void **tmp)
{
	if (e->etype == none)
		((t_json_call_back)tmp[0])(e->node, tmp[1], e->node->type);
	else if (e->etype == string)
		((t_json_call_back)tmp[0])(((t_json_string*)e->node->ptr)->ptr, tmp[1],
			e->node->type);
	else
		((t_json_call_back)tmp[0])(e->node->ptr, tmp[1], e->node->type);
}

inline static int	sf_json_accesses_access(t_jae *e, const char c, va_list ap)
{
	void	*tmp[2];

	if (c == '>')
		return (sf_json_accesses_access_right(e, ap));
	if (c == '<')
	{
		if (e->error_stack && --e->error_stack)
			return (1);
		return ((e->node = e->node->parent) == e->node);
	}
	if (c != '*' && c != '#')
		return (0);
	tmp[0] = va_arg(ap, void*);
	if (c == '#')
		tmp[1] = va_arg(ap, void*);
	if (e->error_stack ||
			(e->etype != none && !ft_json_test_type(e->node, e->etype)))
		return (1);
	if (c == '#')
		sf_json_accesses_access_call(e, tmp);
	else
		sf_json_accesses_access_store(e, tmp[0]);
	return (1);
}

inline static int	sf_json_accesses_type_change(t_jae *e, const char c)
{
	if (c == 'o')
		return ((e->etype = object) == object);
	if (c == 'a')
		return ((e->etype = array) == array);
	if (c == 's')
		return ((e->etype = string) == string);
	if (c == 'b')
		return ((e->etype = boolean) == boolean);
	if (c == 'd')
		return ((e->etype = number) == number);
	if (c == 'i')
		return ((e->etype = integer) == integer);
	if (c == 'n')
		return ((e->etype = null) == null);
	if (c == 'v')
		return ((e->etype = none) == none);
	if (c == 'B')
		return ((e->etype = (boolean | integer)) == (boolean | integer));
	if (c == 'N')
		return ((e->etype = (number | integer)) == (number | integer));
	return (0);
}

int					ft_json_accesses(const t_json_value *root,
									const char *form,
									...)
{
	va_list	ap;
	t_jae	e;
	int		pos;

	if (root == NULL || form == NULL)
		return (-1);
	va_start(ap, form);
	e = (t_jae){.node = NULL, .etype = none, .error_stack = 0};
	pos = -1;
	while (form[++pos] != '\0')
		if (form[pos] == 'r')
			e = (t_jae){.node = (t_json_value*)root, .etype = e.etype,
						.error_stack = 0};
		else if (form[pos] == ' ')
			;
		else if (!sf_json_accesses_type_change(&e, form[pos]) &&
				!sf_json_accesses_access(&e, form[pos], ap))
			{
				va_end(ap);
				return (-1);
			}
	va_end(ap);
	return (0);
}
