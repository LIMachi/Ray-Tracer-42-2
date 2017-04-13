AUTHOR = "hmarot\nhmartzol\npbondoer\nsbouyahi"

NAME = rt

EXEARGS = scenes/full.json

SRCDIR = src
INCDIRS = inc
OBJDIR = .obj

CFLAGS = -Wall -Wextra -Werror -Wno-deprecated -Wno-deprecated-declarations -g
PINC = libft/inc libftx2/inc libftocl/inc libftjson/inc $(HOME)/.brew/include
LPINC = minilibx_X11
MPINC = minilibx_macos
CLIB = libft libftx2 libftocl libftjson
LCLIB = minilibx_X11
MCLIB = minilibx_macos
LLIB = libftx2/libftx2.a libftocl/libftocl.a libftjson/libftjson.a libft/libft.a minilibx_X11/libmlx.a
MLIB = libftx2/libftx2.a libftocl/libftocl.a libftjson/libftjson.a libft/libft.a minilibx_macos/libmlx.a
LLARGS = -lOpenCL -ICL -lXext -lX11
MLARGS = -L$(HOME)/.brew/lib -lglfw -lglew -framework OpenCL -framework OpenGL -framework AppKit

include Makefiles/Makefile.gen
