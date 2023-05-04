CC			= g++ -g -std=gnu++14
MINILIBX	= mlx-linux/libmlx.a
NAME		= so_long
SRCS 		= src/so_long.cpp src/convert_xpms.cpp src/ft_create_map.cpp src/ft_init_map.cpp src/ft_split_fs.cpp src/key_events.cpp src/so_long_utils.cpp src/Client.cpp

all: $(NAME)

$(NAME): $(MINILIBX)
	$(CC) $(SRCS) -o $(NAME) mlx-linux/libmlx.a -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz 

$(MINILIBX):
	make -C mlx-linux
	@echo "MINILIBX compile edildi !"

clean:
	rm -rf $(NAME)

re: clean all

.PHONY: clean run re all norm
