# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wta <wta@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/27 13:03:04 by wta               #+#    #+#              #
#    Updated: 2019/03/01 13:54:45 by wta              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

_GREEN		=	\033[0;32m
_WHITE		=	\033[m
_YELLOW		=	\033[0;33m
_DYELLOW	=	\x1b[33;01m
# VARIABLES #
MKFILEPATH := $(abspath $(lastword $(MAKEFILE_LIST)))
CURRDIR := $(notdir $(patsubst %/,%,$(dir $(MKFILEPATH))))
NAME		=	rtv1
SRCSDIR		=	srcs
LIBFTPATH	=	libft
LIBFTLIB	=	libft.a
LIBFT		=	$(addprefix $(LIBFTPATH)/, $(LIBFTLIB))
INCDIR		=	includes
MLXDIR		= 	minilibx_macos
OBJDIR		=	objs
OBJ			=	$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
CC			=	gcc
INC			=	-I $(INCDIR) -I $(MLXDIR)
CFLAGS		=	-Wall -Wextra -Werror -Ofast
MLXLIB		=	-L $(MLXDIR) -lmlx
MLXFLAG		=	-framework OpenGL -framework Appkit
SRCS=				\
camera.c			\
color.c				\
destroy_rtv1.c		\
event.c				\
event_pressed.c		\
event_released.c	\
intersect.c			\
lights.c			\
list.c				\
normal.c			\
main.c				\
quadratic.c			\
quaternions.c		\
quaternions_2.c		\
raytracing.c		\
read_file.c			\
read_file_helper.c	\
read_file_helper2.c	\
read_file_helper3.c	\
read_file_helper4.c	\
utils.c				\
utils_2.c			\
utils_3.c			\
vectors.c			\
vectors_2.c			\
vectors_3.c			\
thread.c
HEADER		=	\
rtv1.h			\
quaternions.h	\
utils.h			\
vectors.h
# RULES #
all : $(NAME)
# NAME #
$(NAME) : $(LIBFT) $(OBJ)
	@$(MAKE) -C $(MLXDIR)
	@$(CC) $(CFLAGS) $(MLXLIB) $(MLXFLAG) $(INC) $(OBJ) $(LIBFT) -o $@
	@echo "$(_GREEN)[CREATED]$(_WHITE)" $@
	@echo "All objects files are in $(_DYELLOW)/obj$(_WHITE)"
# MKDIROBJ #
$(OBJDIR) :
	@mkdir $@
	@echo "$(_YELLOW)[CREATED]$(_WHITE)" $@/
# RTv1 #
$(addprefix $(OBJDIR)/,%.o) : $(addprefix $(SRCSDIR)/,%.c) $(addprefix $(INCDIR)/,$(HEADER)) | $(OBJDIR)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@echo "$(_GREEN)[OK]$(_WHITE) /$@"
# LIBFT #
$(LIBFT) :
	@make -C $(LIBFTPATH)
	@echo "$(_GREEN)[OK]$(_WHITE) $@"
norm :
	norminette libft/**/*.[ch] srcs/*.c includes/*.h
# CLEAN LIBFT#
clean_mlx:
	@$(MAKE) -C $(MLXDIR) clean
clean_libft:
	@make -C $(LIBFTPATH) clean
# CLEAN_RTv1 #
clean_rtv1 :
	@rm -f $(OBJ)
	@echo "$(_DYELLOW)[CLEAN] (RTv1)$(_WHITE)" /$(OBJDIR)/*.o
	@rm -rf $(OBJDIR)
	@echo "$(_DYELLOW)[CLEAN] (RTv1)$(_WHITE)" /$(OBJDIR)
# FCLEAN LIBFT#
fclean_libft:
	@make -C $(LIBFTPATH) fclean
# CLEAN #
clean : clean_libft clean_mlx
	@rm -f	$(NAME)
	@echo "$(_DYELLOW)[FCLEAN] (RTv1)$(_WHITE)" /$(NAME)

# FCLEAN #
fclean : clean_rtv1 fclean_libft clean_mlx
	@rm -f	$(NAME)
	@echo "$(_DYELLOW)[FCLEAN] (RTv1)$(_WHITE)" $(NAME)
# RE #
re : fclean all
#==============================================================================#
