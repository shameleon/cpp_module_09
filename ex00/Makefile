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
NAME		= btc

###### sources ######	
SRC_FILES	= \
				BitcoinExchange.cpp \
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

##### Download .tgz file for ex00 bitcoin data #####
DATA_DIR		= "./cpp_09"
INTRA42_LINK	= "https://cdn.intra.42.fr/document/document/17265/cpp_09.tgz" 
TGZ_FILE		= "./cpp_09.tgz"
INPUT_DATA		= "date | value\n2011-01-03 | 3\n2011-01-03 | 2\n2011-01-03 | 1n\2011-01-03 | 1.2n\2011-01-09 | 1\n2012-01-11 | -1\n2001-42-42\n2012-01-11 | 1\n2012-01-11 | 2147483648\n2008-12-14 | 1.42\n2022-12-14 | 3.21\n2018/02-03 | 1\n2018-02-30 | 1\n2018-02-03 | 0\n2018-02-03 | 1002\n2022-03-29 | 0.1\n2022-04-01 | 0.1\n2022-04-03 | 0.1"
INPUT_FILE		= ${DATA_DIR}/input.txt

############################
######    R.u.l.e.s   ######
############################
all: $(NAME)

$(NAME): $(OBJ)
	$(COL_ORANGE)
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

data:
	$(COL_BLU)
	@if [ ! -d $(DATA_DIR) ]; then \
		wget $(INTRA42_LINK); \
		tar -xvzf $(TGZ_FILE); \
		rm -rf $(TGZ_FILE); \
		echo $(INPUT_DATA) > $(INPUT_FILE); \
		echo "cpp_09/input.txt"; \
		fi	

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
	leaks -atExit -- ./$(NAME) $(INPUT_FILE)

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all -s ./$(NAME) $(INPUT_FILE)

.PHONY : data valgrind leaks re fclean clean 

-include ${DEP}

##### ANSI Escape Codes #####
COL_RED = @echo "\033[1;31m"
COL_GRN = @echo "\033[1;32m"
COL_YEL = @echo "\033[1;33m"
COL_BLU = @echo "\033[1;34m"
COL_PUR = @echo "\033[1;35m"
COL_CYA = @echo "\033[1;36m"
COL_ORANGE = @echo "\033[1;38:5:214m"
COL_RESET = @echo "\033[0m"
