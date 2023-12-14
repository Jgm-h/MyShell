NAME = minishell
CC = gcc
RM = rm
CFLAGS = -Wall -Wextra -Werror -g -I./libft/includes -I./headers


SRCS = ./main.c \
		./minishell.c \
		./init.c \
		./exec.c \
		./parser.c \
		./lexer.c \
		./lexer_utils.c \
		./quotes.c \
		./parser.c \
		./signals.c \

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
			./srcs/signals

OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

SAN =	-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all \
		-fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow \
		-fno-sanitize=null -fno-sanitize=alignment

vpath %.c $(SRCS_DIR)

all : $(NAME)
$(NAME) : $(OBJS)
	$ make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS)  $(SAN) $(LIBFT_A) -o $@ $^ -lreadline -L$(HOME)/.brew/opt/readline/lib


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