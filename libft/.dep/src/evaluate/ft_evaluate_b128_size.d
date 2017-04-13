.obj/src/evaluate/ft_evaluate_b128_size.o: \
  src/evaluate/ft_evaluate_b128_size.c \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/8.0.0/include/stddef.h \
  /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/../lib/clang/8.0.0/include/__stddef_max_align_t.h
	@printf 'o'
	@gcc   -Wall -Wextra -Werror -g  -Iinc  -Ift_printf/inc  -c src/evaluate/ft_evaluate_b128_size.c -o  .obj/src/evaluate/ft_evaluate_b128_size.o
	@printf '\b✔'