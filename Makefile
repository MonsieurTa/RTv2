# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/01 02:51:44 by wta               #+#    #+#              #
#    Updated: 2019/01/24 00:22:59 by wta              ###   ########.fr        #
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
LIBFT		=	$(addprefix $(LIBFTPATH)/,$(LIBFTLIB))
INCDIR		=	includes
MLXDIR		= 	minilibx_macos
OBJDIR		=	objs
OBJ			=	$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
CC			=	gcc -g -fsanitize=address
INC			=	-I $(INCDIR) -I $(MLXDIR)
CFLAGS		=	-Wall -Wextra -Werror -Ofast
MLXLIB		=	-L $(MLXDIR) -lmlx
MLXFLAG		=	-framework OpenGL -framework Appkit
SRCS=			\
camera.c		\
error.c			\
event.c			\
list.c			\
main.c			\
obj.c			\
quadratic.c		\
raytracing.c	\
view.c			\
vectors.c		\
vectors_2.c
HEADER		=	\
rtv1.h			\
vectors.h
# RULES #
all : $(NAME)
# NAME #
$(NAME) : $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(MLXLIB) $(MLXFLAG) $(INC) $(OBJ) $(LIBFT) -o $@
	@echo "\n$(_GREEN)[CREATED]$(_WHITE)" $@
	@echo "All objects files are in $(_DYELLOW)/obj$(_WHITE)"
# MKDIROBJ #
$(OBJDIR) :
	@mkdir $@
	@echo "\n$(_YELLOW)[CREATED]$(_WHITE)" $@/
# RTv1 #
$(addprefix $(OBJDIR)/,%.o) : $(addprefix $(SRCSDIR)/,%.c) $(addprefix $(INCDIR)/,$(HEADER)) | $(OBJDIR)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<
	@echo "\r                                                              \r\c"
	@echo "$(_GREEN)[OK]$(_WHITE) /$@\c"
# LIBFT #
$(LIBFT) :
	@make -C $(LIBFTPATH)
	@echo "\r                                                              \r\c"
	@echo "$(_GREEN)[OK]$(_WHITE) $@\c"
norm :
	norminette libft/**/*.[ch] srcs/*.c includes/*.h
# CLEAN LIBFT#
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
clean : clean_libft
	@rm -f	$(NAME)
	@echo "$(_DYELLOW)[FCLEAN] (RTv1)$(_WHITE)" /$(NAME)

# FCLEAN #
fclean : clean_rtv1 fclean_libft
	@rm -f	$(NAME)
	@echo "$(_DYELLOW)[FCLEAN] (RTv1)$(_WHITE)" $(NAME)
# RE #
re : fclean all
#==============================================================================#
