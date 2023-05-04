CC			= g++ -g -std=gnu++14
MINILIBX	= minilibx/libmlx.a
FLAGS		=
LFLAGS		= -framework OpenGL -framework AppKit
NAME		= so_long
SRCS 		= src/so_long.cpp src/convert_xpms.cpp src/ft_create_map.cpp src/ft_init_map.cpp src/ft_split_fs.cpp src/key_events.cpp src/so_long_utils.cpp src/Client.cpp

all: $(NAME)

$(NAME): $(MINILIBX)
	$(CC) $(LFLAGS) $(FLAGS) $(SRCS) -o $(NAME) minilibx/libmlx.a

$(MINILIBX):
	make -C minilibx
	@echo "MINILIBX compile edildi !"

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: clean run fclean re all norm
