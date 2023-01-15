# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pharbst <pharbst@student.42heilbronn.de    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/26 07:27:01 by pharbst           #+#    #+#              #
#    Updated: 2022/12/09 09:34:44 by pharbst          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL		=	/bin/bash

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
TICK			=	$(shell echo -e "\xE2\x9C\x94")

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
PRONAME		=	Philosophers

# srcfiles
SRC_NAME	=	main.c \
				execute_sim.c \
				philo_atoi.c \
				ft_calloc.c\
				philo.c\
				time.c\
				ft_bzero.c\
				

# directorys
INC_DIR		=	includes/
SRC_DIR		=	src/*/
OBJ_DIR		=	obj/

# Include
INC_SRC		=	-I includes/

# object
OBJ_NAME	=	$(SRC_NAME:.c=.o)
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_NAME))
SRC			=	$(addprefix $(SRC_DIR), $(SRC_NAME))

# rules
all:
	@./spinner.sh make -s $(NAME)

$(NAME):	header obj_header $(OBJ) linking_header
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"

$(OBJ_DIR)%.o:	$(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -o $@ -c $^ $(INC_SRC)

clean: header
	@./spinner.sh make -s cleansimple

cleansimple:
	@printf "$(FRed)cleaning$(RESET)							  "
	@rm -rf $(OBJ_DIR)
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"

fclean: header
	@./spinner.sh make -s cleanall

cleanall:
	@printf "$(FRed)FCleaning$(RESET)						  	  "
	@rm -rf $(OBJ_DIR)
	@rm -rf $(NAME)
	@printf "$(FGreen)[$(TICK)]\n$(RESET)"

re:
	@./spinner.sh make -s header cleanall $(NAME)

header:
	@printf "$(FYellow)╔═══════════════════════════════════════════════════════════════════╗\n\
║    ______ _     _ _                       _                       ║\n\
║    | ___ \ |   (_) |                     | |                      ║\n\
║    | |_/ / |__  _| | ___  ___  ___  _ __ | |__   ___ _ __ ___     ║\n\
║    |  __/| '_ \| | |/ _ \/ __|/ _ \| '_ \| '_ \ / _ \ '__/ __|    ║\n\
║    | |   | | | | | | (_) \__ \ (_) | |_) | | | |  __/ |  \__ \\    ║\n\
║    \_|   |_| |_|_|_|\___/|___/\___/| .__/|_| |_|\___|_|  |___/    ║\n\
║                                    | |                            ║\n\
║                                    |_|                            ║\n\
╚═══════════════════════════════════════════════════════════════════╝\n"

obj_header:
	@printf "$(FBlue)Compiling .o files$(RESET)						  "

linking_header:
	@printf "$(FGreen)[$(TICK)]\n$(Green)Linking $(PRONAME)$(RESET)						  "

git:	commit push

commit:
	git commit -m "$(msg)"

push:
	git push -u $(branch)

update:
	git pull