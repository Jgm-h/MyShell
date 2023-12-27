NAME = minishell
CC = gcc
RM = rm
CFLAGS = -Wall -Wextra -Werror -g -I./libft/includes -I./headers


SRCS = ./main.c \
		./minishell.c \
		./signals.c \
		./init.c \
		./lexer.c \
		./lexer_token.c \
		./lexer_token2.c \
		./lexer_token3.c \
		./lexer_utils.c \
		./quotes.c \
		./parser.c \
		./exec.c \
		./exec_redir.c \
		./one_cmd.c \
		./utils1.c \
		./echo.c \
        ./cd.c	\
        ./pwd.c \
        ./export.c \
        ./unset.c \
        ./env.c \
        ./exit.c \
        ./free_all.c \
        ./if_tree.c


OBJS_DIR = ./objs
LIBFT_DIR = ./libft
LIBFT_A = ./libft/libft.a
SRCS_DIR = ./srcs/main \
			./srcs/exec \
			./srcs/free \
			./srcs/init \
			./srcs/lexer \
			./srcs/builtins \
			./srcs/parser \
			./srcs/signals \
			./srcs/utils \
			./srcs/free

OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

SAN =	-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all \
		-fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow \
		-fno-sanitize=null -fno-sanitize=alignment

vpath %.c $(SRCS_DIR)

all : $(NAME)
$(NAME) : $(OBJS)
	$ make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS)  $(SAN) $(LIBFT_A) -o $@ $^ -lreadline -L$(HOME)/.brew/opt/readline/lib

test: test.c
	gcc -o test test.c

$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o : %.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -I$(HOME)/.brew/opt/readline/include -o $@ -c $^

debug:
	@$(MAKE) -n $(NAME)

clean :
	@$(RM) -rf $(OBJS_DIR)

fclean : clean
	@$(RM) $(NAME)

re : fclean all