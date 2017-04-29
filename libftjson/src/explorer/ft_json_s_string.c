#include <libftjson.h>
#include <libft.h>

t_json_string ft_json_s_string(char *str)
{
	if (str == NULL)
		return ((t_json_string){.length = 0, .ptr = NULL});
	return ((t_json_string){.length = ft_strlen(str), .ptr = str});
}
