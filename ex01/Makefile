# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmouaike <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/27 08:51:08 by jmouaike          #+#    #+#              #
#    Updated: 2023/04/27 08:51:12 by jmouaike         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###### binary ######	
NAME		= RPN

###### sources ######	
SRC_FILES	= \
				Rpn.cpp \
				main.cpp \

###### directories ######	
SRC_DIR		= ./src/
INC_DIR		= ./inc/
OBJ_DIR		= ./obj/
DEP_DIR		= ./dep/

###### files ######	
SRC			= $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			= $(addprefix $(OBJ_DIR), $(SRC_FILES:.cpp=.o))
DEP			= $(addprefix $(DEP_DIR), $(SRC_FILES:.cpp=.d))

##### Compiler settings #####
CXX			= c++
CXXFLAGS	= -std=c++98
CFLAGS		= -Wall -Werror -Wextra
# 
CFLAGS		+= -Wconversion
#DEBUG		= -g3
# -fsanitize=address
# -Wshadow -Wno-shadow
DEPFLAGS	= -MMD -MP -MF $(DEP_DIR)$*.d

############################
######    R.u.l.e.s   ######
############################
all: $(NAME)

$(NAME): $(OBJ)
	$(COL_CYA)
	$(CXX) $(CXXFLAGS) $(CFLAGS) $(OBJ) -o $(NAME) 
	$(COL_GRN)
	@echo "./$(NAME) executable is ready !"
	$(COL_RESET)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(DEP_DIR)
	$(COL_YEL)
	$(CXX) $(CXXFLAGS) $(CFLAGS) $(VERBOSE_MODE) $(DEPFLAGS) -c $< -o $@
	$(COL_RESET)

clean: $(OBJ_DIR)
	$(COL_RED)
	rm -rfv $(OBJ) $(DEP)
	rmdir $(OBJ_DIR) $(DEP_DIR)
	$(COL_RESET)

fclean: clean
	$(COL_PUR)
	rm -rfv $(NAME)
	$(COL_RESET)

re: fclean all

leaks: $(NAME)
	leaks -atExit -- ./$(NAME)

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all -s ./$(NAME)

.PHONY : valgrind leaks re fclean clean 

-include ${DEP}

##### ANSI Escape Codes #####
COL_RED = @echo "\033[1;31m"
COL_GRN = @echo "\033[1;32m"
COL_YEL = @echo "\033[1;33m"
COL_BLU = @echo "\033[1;34m"
COL_PUR = @echo "\033[1;35m"
COL_CYA = @echo "\033[1;36m"
COL_ORANGE = @echo "\033[38;5;255;165;0m"
COL_RESET = @echo "\033[0m"
