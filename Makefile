# COLORS
RESET		=	\033[0m
BLACK		= 	\033[30m
RED			=	\033[31m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
PURPLE		=	\033[35m
CYAN		=	\033[36m
WHITE		=	\033[37m

# FILE
SRCS 	= main.c control.c
LIBFT 	= libft/ft_bzero.c libft/ft_memset.c libft/ft_calloc.c \
		  libft/ft_substr.c libft/ft_strdup.c libft/ft_strlen.c \
		  libft/ft_strjoin.c libft/ft_strncmp.c libft/ft_split.c \
		  libft/ft_strchr.c  libft/ft_strlcpy.c

TOKEN	= token/tokenize.c token/token_lst.c
LEXER	= lexer/lexerize.c lexer/lexer_lst.c lexer/quote.c lexer/dollar1.c

ENV		= env/environment.c

# COMMAND
SUCCESS		=	@echo "$(GREEN)BUILD SUCCESSFULL !$(RESET)"
REMOVE		=	@echo "$(RED)Deleted !$(RESET)"


# VARIABLES
NAME		=	minishell
OBJ			=	$(SRCS:%.c=%.o)  \
				$(LIBFT:%.c=%.o) \
				$(TOKEN:%.c=%.o) \
				$(ENV:%.c=%.o)   \
				$(LEXER:%.c=%.o)

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