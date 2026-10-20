NAME		?= cub3D
OBJ_DIR		?= obj

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g -std=gnu99
INCLUDES	= -I. -I$(MLX_DIR) -I$(LIBFT_DIR)/Includes \
			-Ilib/parsing/includes -Ilib/parsing/gnl

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
MLX_DIR		= lib/mlx_linux
MLX			= $(MLX_DIR)/libmlx.a
# NAME, OBJ_DIR and CFLAGS are set explicitly: otherwise the sub-makes inherit
# our command-line NAME (e.g. NAME=cub3D) and MLX never produces libmlx.a.
MLX_MAKE	= $(MAKE) -s -C $(MLX_DIR) -f Makefile.mk NAME=libmlx.a OBJ_DIR=obj INC=/usr/include CFLAGS="-O3 -I/usr/include -std=gnu99"
LIBS		= -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm

SRC_ENGINE	= main.c \
			lib/collision/clipping.c \
			lib/exit/exit.c \
			lib/graphics/image_manip.c \
			lib/graphics/texture.c \
			lib/key_handling/key_handling.c \
			lib/object/player.c \
			lib/object/raycast.c \
			lib/render/loop.c \
			lib/render/render.c \
			lib/vector/vector2.c

SRC_PARSING	= lib/parsing/init.c \
			lib/parsing/parse_file.c \
			lib/parsing/parse_line.c \
			lib/parsing/parse_check.c \
			lib/parsing/parse_map.c \
			lib/parsing/parse_walls.c \
			lib/parsing/parse_texture.c \
			lib/parsing/parse_utils.c \
			lib/parsing/utils.c \
			lib/parsing/free.c \
			lib/parsing/find_char.c \
			lib/parsing/gnl/get_next_line.c \
			lib/parsing/gnl/get_next_line_utils.c

SRC			= $(SRC_ENGINE) $(SRC_PARSING)
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP			= $(OBJ:.o=.d)

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -MMD -MP -c $< -o $@

# Sub-libraries are always delegated to their own Makefiles, which only rebuild
# what is out of date. $(NAME) is relinked only when an archive really changes.
$(LIBFT): FORCE
	@$(MAKE) -s -C $(LIBFT_DIR) NAME=libft.a

$(MLX): FORCE
	@$(MLX_MAKE)

FORCE:

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) -s -C $(LIBFT_DIR) NAME=libft.a clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -s -C $(LIBFT_DIR) NAME=libft.a fclean
	@$(MLX_MAKE) clean

re: fclean all

-include $(DEP)

.PHONY: all clean fclean re FORCE
