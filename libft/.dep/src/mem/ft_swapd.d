.obj/src/mem/ft_swapd.o: src/mem/ft_swapd.c
	@printf 'o'
	@gcc   -Wall -Wextra -Werror -g  -Iinc  -Ift_printf/inc  -c src/mem/ft_swapd.c -o  .obj/src/mem/ft_swapd.o
	@printf '\b✔'