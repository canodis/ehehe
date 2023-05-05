CC			= g++ -g -std=gnu++14
MINILIBX	= mlx-mac/libmlx.a
NAME		= so_long_multiplayer
SRCS 		= src/so_long.cpp src/convert_xpms.cpp src/ft_create_map.cpp src/ft_init_map.cpp src/ft_split_fs.cpp src/key_events.cpp src/so_long_utils.cpp src/Client.cpp
MFLAGS		= -framework OpenGL -framework AppKit
LFLAGS		= -Lmlx_linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(MINILIBX)
	$(CC) $(MFLAGS) $(SRCS) -o $(NAME) mlx-mac/libmlx.a
	@echo "./so_long_multiplayer [kullanici_adi]"

$(MINILIBX):
	make -C mlx-linux
	@echo "MINILIBX compile edildi !"

clean:
	rm -rf $(NAME)

re: clean all

.PHONY: clean run re all norm
