NAME = simple_interpreter

CC = clang++
DEBUG_FLAG = -g -Wfatal-errors -Wpedantic -Wconversion -Wshadow
CC_FLAGS = -Wall -Wextra -Werror #-std=c++98 -g #${DEBUG_FLAG}


SRCS =	srcs/main.cpp\
		srcs/Node.cpp\
		srcs/Token.cpp\
		srcs/Lexer.cpp\
		srcs/Parser.cpp\
		srcs/Interpreter.cpp\



OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)
OBJS_DIR = ./objs
DEP = $(OBJS:%.o=%.d)
HEADER = -I ./includes/

all				: 	${NAME}
$(NAME) 		: 	$(OBJS)	
						mkdir -p $(@D)
						$(CC) $(CC_FLAGS) $^ -o $@
-include $(DEP)
$(OBJS_DIR)/%.o	:	%.cpp
						mkdir -p $(@D)
						$(CC) $(CC_FLAGS) ${HEADER} -MMD -c $< -o $@




clean	:
				rm -rf $(OBJS_DIR) 
fclean	:	clean
				rm -rf ${NAME}  
re		:	fclean
				make all
.PHONY : all clean fclean re 

