CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes/mlx

MFLAGS = -Lincludes/mlx -lmlx -lXext -lX11 -lm -lbsd

NAME = cub3D

LIBFT_DIR = libft

LIB = $(LIBFT_DIR)/libft.a

SRC =cub3d.c events/close_program.c  events/handle_keys.c events/handle_mouse.c events/destroy.c \
	game/game_loop.c game/init_game.c game/set_player.c game/init_minilibx.c game/door_system.c \
	parser/check_map.c parser/parse_colors.c parser/parse_file.c parser/parse_map.c parser/parse_textures.c parser/flood_fill.c parser/door_parsing.c parser/ft_handle.c parser/ft_check.c \
	render/draw_walls.c  render/raycasting.c render/render_frame.c render/texture_mapping.c  render/render_colors.c  render/draw_mini_map.c \
	 textures/load_textures.c \
	utils/ft_error.c utils/ft_free.c utils/ft_utils.c  \
	get_next_line/get_next_line.c

OBJ= $(SRC:.c=.o)

all: $(NAME) 

$(LIB):
	make all -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(MFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

run: maps/good/cheese_maze.cub
	./cub3D maps/good/cheese_maze.cub