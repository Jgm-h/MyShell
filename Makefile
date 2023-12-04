NAME = philo
CC = gcc
RM = rm
CFLAGS = -Wall -Wextra -Werror -g -pthread


SRCS = ./main.c \
		./init.c \
		./threads.c \
		./utils.c \
		./frees.c \
		./actions.c \
		./child.c \
		./utils_mutex.c \
		./utils_mutex2.c \
		./prints.c \
		./forks.c

OUTPUT_DIR = ./philo
OBJS_DIR = ./philo/objs
INC_DIR1 =	./philo/headers
SRCS_DIR = philo/srcs \

OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

SAN =	-fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all \
		-fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow \
		-fno-sanitize=null -fno-sanitize=alignment

vpath %.c $(SRCS_DIR)

all : $(OUTPUT_DIR)/$(NAME)
$(OUTPUT_DIR)/$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(SAN) $(LIBS) -o $@ $^

$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o : %.c | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -o $@  -I$(INC_DIR1) -c $^

debug:
	@$(MAKE) -n $(NAME)

clean :
	@$(RM) -rf $(OBJS_DIR)

fclean : clean
	@$(RM) $(OUTPUT_DIR)/$(NAME)

re : fclean all