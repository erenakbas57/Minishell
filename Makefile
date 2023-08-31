# COLORS
RESET 			=\033[0m
BLACK 			=\033[30m
WHITE 			=\033[37m
RED 			=\033[31m
LIGHT_RED 		=\033[91m
GREEN 			=\033[32m
LIGHT_GREEN 	=\033[92m
YELLOW 			=\033[33m
LIGHT_YELLOW 	=\033[93m
BLUE 			=\033[34m
LIGHT_BLUE 		=\033[94m
MAGENTA 		=\033[35m
LIGHT_MAGENTA 	=\033[95m
CYAN 			=\033[36m
LIGHT_CYAN 		=\033[96m
GREY 			=\033[90m
LIGHT_GREY 		=\033[37m

BLACK_BOLD 		=\033[1;30m
RED_BOLD 		=\033[1;31m
GREEN_BOLD 		=\033[1;32m
YELLOW_BOLD 	=\033[1;33m
BLUE_BOLD 		=\033[1;34m
MAGENTA_BOLD 	=\033[1;35m
CYAN_BOLD 		=\033[1;36m
WHITE_BOLD 		=\033[1;37m

# FILE
SRCS 	= main.c control.c free.c
LIBFT 	= libft/ft_bzero.c libft/ft_memset.c libft/ft_calloc.c \
		  libft/ft_substr.c libft/ft_strdup.c libft/ft_strlen.c \
		  libft/ft_strjoin.c libft/ft_strncmp.c libft/ft_split.c \
		  libft/ft_strchr.c  libft/ft_strlcpy.c libft/ft_strcmp.c

TOKEN	= token/tokenize.c token/token_lst.c
LEXER	= lexer/lexerize.c lexer/lexer_lst.c lexer/quote.c lexer/dollar.c
BUILTIN = builtin/pwd.c builtin/builtin.c builtin/cd.c builtin/exit.c \
		  builtin/env.c builtin/echo.c builtin/export.c builtin/unset.c
ENV		= env/environment.c 
CMD		= cmd/cmd.c

# COMMAND
SUCCESS		=	@echo "$(GREEN)BUILD SUCCESSFULL !$(RESET)"
REMOVE		=	@echo "$(RED)Deleted !$(RESET)"


# VARIABLES
NAME		=	minishell
OBJ			=	$(SRCS:%.c=%.o)  \
				$(LIBFT:%.c=%.o) \
				$(TOKEN:%.c=%.o) \
				$(ENV:%.c=%.o)   \
				$(LEXER:%.c=%.o) \
				$(CMD:%.c=%.o) \
				$(BUILTIN:%.c=%.o)

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
READLINE	=	-lreadline
RM			=	rm -rf


all: $(NAME)

$(NAME)	:	$(OBJ)
			@echo "\n"
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(READLINE)
			$(SUCCESS)

%.o: %.c
			@echo "$(CYAN)Generating minishell objects...$(RESET)"
			@${CC} ${CFLAGS} -c $< -o $@

clean	:
			$(RM) $(OBJ)
			$(REMOVE)

fclean	:	clean
			$(RM) $(NAME)
			$(REMOVE)
		
re		:	fclean all

run		: all
		  clear
		  ./$(NAME)

.PHONY: all re clean fclean