NAME = simple_interpreter

CC = clang++
DEBUG_FLAG = -g -Wfatal-errors -Wshadow
CC_FLAGS = -Wall -Wextra -Werror   ${DEBUG_FLAG}

OBJS_DIR = ./objs
SRCS_DIR = ./srcs

SRCS =	$(addprefix $(SRCS_DIR)/, \
		main.cpp\
		Node.cpp\
		Token.cpp\
		Lexer.cpp\
		Parser.cpp\
		Interpreter.cpp\
		Coefficient.cpp\
		)


OBJS = $(SRCS:%.cpp=$(addprefix $(OBJS_DIR)/, %.o))
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

