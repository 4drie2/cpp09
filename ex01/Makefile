# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abidaux <abidaux@student.42lehavre.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/08/25 16:05:51 by abidaux           #+#    #+#              #
#    Updated: 2026/08/26 11:18:03 by abidaux          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Compiler and flags
CXX			= c++
CXXFLAGS	= -Wall -Wextra -Werror -std=c++98

# Project name
NAME		= RPN

# Folders
SRC_DIR		= src
OBJ_DIR		= obj
INC_DIR		= include

# Colors
GREEN		= \033[1;32m
CYAN		= \033[1;36m
YELLOW		= \033[1;33m
RED			= \033[1;31m
RESET		= \033[0m

# Sources
SRC_FILES	=	main.cpp \
				RPN.cpp

# Object files
OBJ_FILES	= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.cpp=.o))

# Include headers
INCLUDES	= -I$(INC_DIR)

# Default rule
all: $(NAME)

# Link objects to create the binary
$(NAME): $(OBJ_FILES)
	@printf "$(CYAN)Linking $(NAME)...$(RESET)\n"
	@$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $(NAME) && \
		printf "$(GREEN)✓ $(NAME) ready!$(RESET)\n"

# Compile .cpp to .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@printf "$(YELLOW)Compiling $<...$(RESET)\n"
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Ensure obj/ exists
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Clean object files
clean:
	@printf "$(RED)Cleaning object files...$(RESET)\n"
	@rm -rf $(OBJ_DIR)

# Clean everything
fclean: clean
	@printf "$(RED)Removing executable...$(RESET)\n"
	@rm -f $(NAME)

# Rebuild
re: fclean all

# Avoid make interpreting these names as filenames
.PHONY: all clean fclean re