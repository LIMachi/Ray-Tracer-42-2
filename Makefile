AUTHOR = "hmarot\nhmartzol\npbondoer\nsbouyahi"

NAME = rt

EXEARGS = scenes/full.json

SRCDIR = src
INCDIRS = inc
OBJDIR = .obj

ITEMS = argn \
	cam \
	cl_float4_operations \
	cl_vector_from_json_array \
	main \
	cmd \
	out \
	mouse \
	direct_output \
	materials \
	textures_holder \
	parser/check_parsed_data \
	parser/default_material \
	parser/parse_camera \
	parser/parse_lights \
	parser/parse_objects \
	parser/parse_render_options \
	parser/parse_materials \
	parser/parse_images \
	parser/parse_texture \
	parser/parser \
	prim \
	rt \
	update_kernel_args \
	lights \
	ft_vector_thales

CFLAGS = -Wall -Wextra -Werror -Wno-deprecated -Wno-deprecated-declarations -g -O2
PINC = libft/inc libftx2/inc libftocl/inc libftjson/inc
LPINC = minilibx_X11
MPINC = minilibx_macos
CLIB = libft libftx2 libftocl libftjson
LCLIB = minilibx_X11
MCLIB = minilibx_macos
LLIB = libftx2/libftx2.a libftocl/libftocl.a libftjson/libftjson.a libft/libft.a minilibx_X11/libmlx.a
MLIB = libftx2/libftx2.a libftocl/libftocl.a libftjson/libftjson.a libft/libft.a minilibx_macos/libmlx.a
LLARGS = -lOpenCL -ICL -lXext -lX11
MLARGS = -framework OpenCL -framework OpenGL -framework AppKit

include Makefiles/Makefile.gen
