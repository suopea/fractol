NAME	:= fractol
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ./MLX42/

HEADERS	:= -I ./include -I $(LIBMLX)include
LIBS	:= $(LIBMLX)build/libmlx42.a -ldl -lglfw -pthread -lm
SRCS	:= $(shell find ./src -iname "*.c")
OBJS	:= ${SRCS:.c=.o}

all: $(LIBMLX) $(NAME)
	./fractol

d: $(LIBMLX)
	$(CC) $(SRCS) $(LIBS) -g $(HEADERS)
	gdb -tui a.out
	rm a.out

$(LIBMLX):
	git clone https://github.com/codam-coding-college/MLX42.git
	@cmake $(LIBMLX) -B $(LIBMLX)build && make -C $(LIBMLX)build -j4

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(LIBMLX)


re: clean all

# secondary?
.SECONDARY: libmlx
.PHONY: all, clean, fclean, re, libmlx
