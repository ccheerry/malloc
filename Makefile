ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME	:= libft_malloc_$(HOSTTYPE).so
LINK	:= libft_malloc.so

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -fPIC -Iinc
LDFLAGS	:= -shared -pthread

SRC_DIR	:= src
OBJ_DIR	:= obj

SRCS	:= malloc.c \
		   free.c \
		   realloc.c \
		   show_alloc_mem.c

OBJS	:= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
DEPS	:= $(OBJS:.o=.d)

all: $(LINK)

$(LINK): $(NAME)
	ln -sf $(NAME) $(LINK)

$(NAME): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

test: $(LINK)
	$(CC) -Wall -Wextra -Werror -Iinc test/main.c -L. -lft_malloc -o test_malloc
	LD_LIBRARY_PATH=. ./test_malloc

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f libft_malloc_*.so $(LINK) test_malloc

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re test
