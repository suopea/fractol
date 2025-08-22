NAME	:= fractol
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
MLX_DIR	:= ./MLX42
MLX_LIB := $(MLX_DIR)/build/libmlx42.a

HEADERS	:= -I ./include -I $(MLX_DIR)/include
LIBS	:= $(MLX_LIB) -ldl -lglfw -pthread -lm
SRCS	:= $(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: $(MLX_LIB) $(NAME)
	./fractol

repo: $(MLX_LIB)

d: $(MLX_DIR)
	$(CC) $(SRCS) $(LIBS) -g $(HEADERS)
	gdb -tui a.out
	rm a.out

$(MLX_LIB): $(MLX_DIR)
	@cmake $(MLX_DIR)/ -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(MLX_DIR):
	git clone https://github.com/codam-coding-college/MLX42.git

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(MLX_DIR)
	@rm compile_commands.json


re: clean all

# secondary?
.SECONDARY: libmlx
.PHONY: all, clean, fclean, re, libmlx
