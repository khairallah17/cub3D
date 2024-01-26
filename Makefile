NAME		=	cub3D

CC			=	gcc

CFLAGS		=	-Wall -Wextra  -fsanitize=address -g
CMLX42		=  $(PWD)/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
# CMLX42		= $(PWD)/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/agoumi/.brew/opt/glfw/lib/"
# directories
SRC_DIR		=	./
OBJ_DIR		=	./obj/
INC_DIR		=	./

# controll codes
RESET		=	\033[0m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
RED			=	\033[31m
UP			=	\033[A
CUT			=	\033[K

#source files
SRC_FILES	=	gnl/get_next_line_utils.c \
				gnl/get_next_line.c \
				parsing/check_arguments.c \
				parsing/checking_texture_file.c \
				parsing/color_rgb.c \
				parsing/path_xpm.c \
				parsing/check_map.c \
				parsing/parsing.c \
				game_logic/game_hooks.c \
				game_logic/launch.c \
				game_logic/player_mouvements.c \
				game_logic/player.c \
				game_logic/walls_checker.c \
				minimap/draw_minimap.c \
				ray_casting/casting_init.c \
				ray_casting/casting_utils.c \
				ray_casting/horizontal_checker.c \
				ray_casting/vertical_checker.c \
				ray_casting/ray_casting.c \
				rendering/drawing_map.c \
				rendering/drawing_rays.c \
				cub3D.c

INC_FILES	=	gnl/get_next_line.h \
				cub3D.h

OBJ_FILES	=	$(SRC_FILES:.c=.o)

#paths
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

                                                                                
#all rule
all: $(NAME)
	@printf "\n"
	@printf "$(GREEN) ██████╗    ██╗   ██╗    ██████╗     ██████╗     ██████╗ \n$(RESET)"
	@printf "$(GREEN)██╔════╝    ██║   ██║    ██╔══██╗    ╚════██╗    ██╔══██╗\n$(RESET)"
	@printf "$(GREEN)██║         ██║   ██║    ██████╔╝     █████╔╝    ██║  ██║\n$(RESET)"
	@printf "$(GREEN)██║         ██║   ██║    ██╔══██╗     ╚═══██╗    ██║  ██║\n$(RESET)"
	@printf "$(GREEN)╚██████╗    ╚██████╔╝    ██████╔╝    ██████╔╝    ██████╔╝\n$(RESET)"
	@printf "$(GREEN) ╚═════╝     ╚═════╝     ╚═════╝     ╚═════╝     ╚═════╝ \n$(RESET)"
	@printf "\n"

#compile the executable
$(NAME): $(OBJ) $(INC_FILES)
	@echo "$(YELLOW)Compiling [$(NAME)]...$(RESET)"
	@(cd libft; make)
	@(cd MLX42; cmake -B build; cmake --build build -j4)
	@$(CC) $(CFLAGS) $(CMLX42) $(OBJ) ./libft/libft.a -o $(NAME)
	@echo "$(GREEN)Finished [$(NAME)]$(RESET)"

#compile objects
$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(INC_FILES)
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling [$@]...$(RESET)"
	@$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<
	@printf "$(UP)$(CUT)"
	@echo "$(GREEN)Finished [$@]$(RESET)"
	@printf "$(UP)$(CUT)"

#clean rule
clean:
	@if [ -d "$(OBJ_DIR)" ]; then \
	rm -rf $(OBJ_DIR); \
	echo "$(BLUE)Deleting all objects from /Cub3D...$(RESET)"; else \
	echo "No objects to remove from /Cub3D."; \
	fi;

#fclean rule
fclean: clean
	@if [ -f "$(NAME)" ]; then \
	rm -f $(NAME); \
	cd ./libft; make fclean; \
	echo "$(BLUE)Deleting $(NAME) from /Cub3D...$(RESET)"; else \
	echo "No Executable to remove from /Cub3D."; \
	fi;

#re rule
re: fclean all

#phony
.PHONY: all clean fclean re                                                                                  