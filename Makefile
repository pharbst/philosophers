# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/26 07:27:01 by pharbst           #+#    #+#              #
#    Updated: 2022/11/26 07:50:10 by pharbst          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME		=	$(shell uname)
OS			=	$(shell cat /etc/os-release | grep -e NAME | cut -d= -f2 | tr -d '"')
OS_LIKE		=	$(shell cat /etc/os-release | grep ID_LIKE | cut -d= -f2)

# Compiler
CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
CFLAGS			+=	-g
LINUX_FLAGS	=	

# Project
NAME		=	philo

# srcfiles
SRC_NAME	=	main.c \

# directorys
INC_DIR		=	philo/includes/
SRC_DIR		=	philo/src/
OBJ_DIR		=	philo/obj/
LIBFT_DIR	=	libft/

# librarys
LIBFTIO		=	$(LIBFT_DIR)libftio.a

# Include
INC_SRC		=	-I /philo/includes
INC_LIBFT	=	-I $(LIBFT_DIR)includes

# object
OBJ_NAME	=	$(SRC_NAME:.c=.o)
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_NAME))
SRC			=	$(addprefix $(SRC_DIR), $(SRC_NAME))

ifeq ($(UNAME), Linux)
	Black			=	$(shell echo -e "\033[0;30m")
	FBlack			=	$(shell echo -e "\033[1;30m")
	Red				=	$(shell echo -e "\033[0;31m")
	FRed			=	$(shell echo -e "\033[1;31m")
	Green			=	$(shell echo -e "\033[0;32m")
	FGreen			=	$(shell echo -e "\033[1;32m")
	Brown/Orange	=	$(shell echo -e "\033[0;33m")
	FBrown/Orange	=	$(shell echo -e "\033[1;33m")
	FYellow			=	$(shell echo -e "\033[1;33m")
	Yellow			=	$(shell echo -e "\033[0;33m")
	Blue			=	$(shell echo -e "\033[0;34m")
	FBlue			=	$(shell echo -e "\033[1;34m")
	Purple			=	$(shell echo -e "\033[0;35m")
	FPurple			=	$(shell echo -e "\033[1;35m")
	Cyan			=	$(shell echo -e "\033[0;36m")
	FCyan			=	$(shell echo -e "\033[1;36m")
	FWhite			=	$(shell echo -e "\033[1;37m")
	White			=	$(shell echo -e "\033[0;37m")
	RESET			=	$(shell echo -e "\033[0m")
else ifeq ($(UNAME), Darwin)
	Black			=	$(shell echo "\033[0;30m")
	FBlack			=	$(shell echo "\033[1;30m")
	Red				=	$(shell echo "\033[0;31m")
	FRed			=	$(shell echo "\033[1;31m")
	Green			=	$(shell echo "\033[0;32m")
	FGreen			=	$(shell echo "\033[1;32m")
	Brown/Orange	=	$(shell echo "\033[0;33m")
	FBrown/Orange	=	$(shell echo "\033[1;33m")
	FYellow			=	$(shell echo "\033[1;33m")
	Yellow			=	$(shell echo "\033[0;33m")
	Blue			=	$(shell echo "\033[0;34m")
	FBlue			=	$(shell echo "\033[1;34m")
	Purple			=	$(shell echo "\033[0;35m")
	FPurple			=	$(shell echo "\033[1;35m")
	Cyan			=	$(shell echo "\033[0;36m")
	FCyan			=	$(shell echo "\033[1;36m")
	FWhite			=	$(shell echo "\033[1;37m")
	White			=	$(shell echo "\033[0;37m")
	RESET			=	$(shell echo "\033[0m")
else
	$(error Colors for your OS ($(UNAME)) are not supported)
endif

# rules
all: $(NAME)

$(NAME):	$(LIBFTIO) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -L $(LIBFT_DIR) -lftio -o $(NAME)
	@echo "$(FGreen)Done$(RESET)"

$(OBJ_DIR)%.o:	$(SRC_DIR)*/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(FGreen)Compiling:$(RESET) $(notdir $<)"
	@$(CC) $(CFLAGS) -o $@ -c $(INC_LIBFTIO) $^ $(INC_SRC)

$(LIBFTIO):
	@make -C $(LIBFT_DIR)

clean:
	@echo "$(FRed)cleaning$(RESET)"
	@make clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)

fclean:
	@echo "$(FRed)Cleaning$(RESET)"
	@make fclean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	@rm -f $(NAME)

re: fclean all

git:	commit push

commit:
	git commit -m "$(msg)"

push:
	git push -u $(branch)

update:
	git pull
	make update -C ./libft