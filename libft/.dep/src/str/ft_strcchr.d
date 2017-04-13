.obj/src/str/ft_strcchr.o: src/str/ft_strcchr.c
	@printf 'o'
	@gcc   -Wall -Wextra -Werror -g  -Iinc  -Ift_printf/inc  -c src/str/ft_strcchr.c -o  .obj/src/str/ft_strcchr.o
	@printf '\b✔'