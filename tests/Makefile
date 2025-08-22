NAME	:= fractol
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
MLX_DIR	:= ../MLX42
MLX_LIB := $(MLX_DIR)/build/libmlx42.a

HEADERS	:= -I ../include -I $(MLX_DIR)/include
LIBS	:= $(MLX_LIB) -ldl -lglfw -pthread -lm

move: $(MLX_LIB)
	cc ../src/coordinates.c ../src/indexes.c ../src/init.c test_move.c $(HEADERS) $(LIBS) -g
	./a.out

coordinates:
	cc ../src/coordinates.c ../src/indexes.c test_coordinates.c $(HEADERS) -g
	./a.out

none:
	echo "do nothing"

$(MLX_LIB): $(MLX_DIR)
	@cmake $(MLX_DIR)/ -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

$(MLX_DIR):
	git clone https://github.com/codam-coding-college/MLX42.git

clean:
	rm a.out compile_commands.json

.PHONY: all, clean, fclean, re, libmlx
