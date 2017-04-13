.obj/src/mem/ft_swapi.o: src/mem/ft_swapi.c
	@printf 'o'
	@gcc   -Wall -Wextra -Werror -g  -Iinc  -Ift_printf/inc  -c src/mem/ft_swapi.c -o  .obj/src/mem/ft_swapi.o
	@printf '\b✔'