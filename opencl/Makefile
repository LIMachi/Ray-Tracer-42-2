# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cchaumar <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/02/23 12:31:27 by cchaumar          #+#    #+#              #
#    Updated: 2017/04/08 17:38:31 by cchaumar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLG   = -Wextra -Wall -Werror -g2
FILES  = ft_opencl.c kernel.c devices.c run.c
SRCD   = srcs/
OBJD   = objs/
SRCS   = $(addprefix $(SRCD),$(FILES))
OBJS   = $(addprefix $(OBJD),$(FILES:.c=.o))
INCD   = includes/
LIBFT  = ../
GENERIC= ../generics/includes/
HEADERS= ft_opencl.h
HEAD   = $(addprefix $(HEADERS), $(INCD))
INC    = -I$(INCD) -I$(GENERIC) -I$(LIBFT)

.PHONY : all clean

all : $(OBJS)

$(OBJD)%.o: $(SRCD)%.c
	@mkdir -p $(OBJD)
	gcc $(CFLG) $(INC) -c -o $@ $<

clean:
		@rm -f $(OBJS)
		@echo "printf objects cleaned"

re: clean all
