NAME = minishell

READLINE_LIB_DIR_FLAG := -L$(shell brew --prefix readline)/lib
READLINE_INC_DIR_FLAG := -I$(shell brew --prefix readline)/include

SRC =	main.c 					\
		srcs/parsing/parsing.c	srcs/parsing/read_line.c		srcs/parsing/open_close.c	srcs/parsing/heredocs.c	srcs/parsing/variables.c	srcs/parsing/variables2.c	srcs/parsing/parsing2.c		srcs/parsing/createprocess.c	srcs/parsing/variableutils.c	srcs/parsing/handletxt.c	srcs/parsing/createcmd.c\
		srcs/utils/utils.c		srcs/utils/list_addback.c		srcs/utils/list_clear.c		srcs/utils/list_new.c	srcs/utils/list_print.c		srcs/utils/utils2.c			srcs/utils/destroy.c		srcs/utils/utils3.c\
		srcs/builtins/msh_env.c	srcs/builtins/msh_isbuiltin.c	srcs/builtins/msh_echo.c	srcs/builtins/msh_pwd.c	srcs/builtins/msh_export.c	srcs/builtins/msh_export2.c	srcs/builtins/msh_export3.c	srcs/builtins/msh_unset.c		srcs/builtins/msh_cd.c			srcs/builtins/msh_exit.c	\
		srcs/init.c				\
		srcs/exec/exec.c		srcs/exec/exec2.c				srcs/exec/exec3.c\
		srcs/signal/signal.c	
		

OBJ = $(SRC:.c=.o)
OBJSDIR	= objs/

OBJS = $(addprefix $(OBJSDIR), $(OBJ))

FLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
LINKS = libft/libft.a

NONE		='\033[0m'
BLU			='\033[0;34m'
RED			='\033[0;31m'
GREEN		='\033[32m'
GRAY		='\033[2;37m'
CURSIVE		='\033[3m'

all: $(NAME)

$(OBJSDIR)%.o : %.c		hdrs/minishell.h libft/libft.a Makefile
	@mkdir -p $(OBJSDIR)
	@mkdir -p $(OBJSDIR)srcs
	@mkdir -p $(OBJSDIR)srcs/parsing
	@mkdir -p $(OBJSDIR)srcs/utils
	@mkdir -p $(OBJSDIR)srcs/builtins
	@mkdir -p $(OBJSDIR)srcs/exec
	@mkdir -p $(OBJSDIR)srcs/signal
	@gcc $(READLINE_INC_DIR_FLAG) $(FLAGS) -c $< -o $@
	@echo $(CURSIVE)$(GRAY) "     - creating .o ..." $(NONE)

$(NAME): maker $(OBJS)
	@echo $(CURSIVE)$(GRAY) "     - Compiling $(NAME)..." $(NONE)
	@gcc $(FLAGS) $(OBJS) $(READLINE_INC_DIR_FLAG) $(READLINE_LIB_DIR_FLAG) $(LINKS) -lreadline -o $(NAME)
	@echo $(GREEN)"- Compiled -"$(NONE)
#	@rm $(OBJ)
	@echo $(CURSIVE)$(GRAY) "     Deleted object files" $(NONE)

maker:
		@make -C libft

exe: all
	@echo "     - Executing $(NAME)... \n"
	@./$(NAME)
	@echo "\n     - Done -"

clean:
	@echo $(CURSIVE)$(GRAY) "     - Removing object files..." $(NONE)
	@make clean -C libft
	@rm -rf $(OBJ)
	@rm -rf $(OBJSDIR)

fclean: clean
	@echo $(CURSIVE)$(GRAY) "     - Removing $(NAME)..." $(NONE)
	@rm -rf $(NAME)
	@rm -rf libft/libft.a

re: fclean all

.phony: re fclean all clean exe maker