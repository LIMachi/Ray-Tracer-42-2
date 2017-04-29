int	ft_dictionary_search(const char *str, const char **dict, const int size)
{
	int i;
	int j;

	i = -1;
	while (++i < size)
	{
		j = 0;
		while (str[j] == dict[i][j] && str[j] != '\0' && dict[i][j] != '\0')
			++j;
		if (str[j] == '\0' && dict[i][j] == '\0')
			return (i);
	}
	return (-1);
}
