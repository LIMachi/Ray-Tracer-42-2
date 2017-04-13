.obj/src/math/pow10_i128.o: src/math/pow10_i128.c
	@printf 'o'
	@gcc   -Wall -Wextra -Werror -g  -Iinc  -Ift_printf/inc  -c src/math/pow10_i128.c -o  .obj/src/math/pow10_i128.o
	@printf '\b✔'