CC = cc

CFLAGS = -Wall -Wextra -Werror -Iincludes/mlx

MFLAGS = -Lincludes/mlx -lmlx -lXext -lX11 -lm -lbsd

NAME = cub3D
NAME_BONUS = cub3D_bonus

LIBFT_DIR = libft
LIB = $(LIBFT_DIR)/libft.a

SRC = cub3d.c \
	events/close_program.c events/handle_keys.c events/destroy.c \
	game/game_loop.c game/init_game.c game/set_player.c game/init_minilibx.c game/is_wall.c \
	parser/check_map.c parser/parse_colors.c parser/parse_file.c parser/parse_map.c parser/parse_textures.c parser/flood_fill.c parser/ft_handle.c parser/ft_check.c \
	render/draw_walls.c render/raycasting.c render/render_frame.c render/texture_mapping.c render/render_colors.c \
	textures/load_textures.c \
	utils/ft_error.c utils/ft_free.c utils/ft_utils.c \
	get_next_line/get_next_line.c

SRC_BONUS = bonus/cub3d_bonus.c \
	bonus/events_bonus/close_program_bonus.c bonus/events_bonus/handle_keys_bonus.c bonus/events_bonus/destroy_bonus.c bonus/events_bonus/handle_mouse_bonus.c \
	bonus/game_bonus/game_loop_bonus.c bonus/game_bonus/init_game_bonus.c bonus/game_bonus/set_player_bonus.c bonus/game_bonus/init_minilibx_bonus.c bonus/game_bonus/is_wall_bonus.c bonus/game_bonus/door_system_bonus.c \
	bonus/parser_bonus/check_map_bonus.c bonus/parser_bonus/parse_colors_bonus.c bonus/parser_bonus/parse_file_bonus.c bonus/parser_bonus/parse_map_bonus.c bonus/parser_bonus/parse_textures_bonus.c bonus/parser_bonus/flood_fill_bonus.c bonus/parser_bonus/ft_handle_bonus.c bonus/parser_bonus/ft_check_bonus.c bonus/parser_bonus/door_parsing_bonus.c \
	bonus/render_bonus/draw_mini_map_bonus.c bonus/render_bonus/draw_walls_bonus.c bonus/render_bonus/raycasting_bonus.c bonus/render_bonus/render_frame_bonus.c bonus/render_bonus/texture_mapping_bonus.c bonus/render_bonus/render_colors_bonus.c bonus/render_bonus/update_map_bonus.c \
	bonus/textures_bonus/load_textures_bonus.c \
	get_next_line/get_next_line.c \
	bonus/utils_bonus/ft_error_bonus.c bonus/utils_bonus/ft_free_bonus.c bonus/utils_bonus/ft_utils_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all: $(NAME)

$(LIB):
	make all -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(MFLAGS) -o $(NAME)

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS) $(LIB)
	$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIB) $(MFLAGS) -o $(NAME_BONUS)

clean:
	rm -f $(OBJ) $(OBJ_BONUS)
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	make fclean -C $(LIBFT_DIR)

re: fclean all
