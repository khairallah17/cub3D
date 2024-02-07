NAME		=	cub3D
BONUS		=	cub3D_Bonus

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra
CMLX42		=  $(PWD)/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"
# CMLX42		= $(PWD)/MLX42/build/libmlx42.a -Iinclude -lglfw -L"/Users/agoumi/.brew/opt/glfw/lib/"
# directories
SRC_DIR		=	./
BNS_DIR		=	./bonus/
OBJ_DIR		=	./obj/
OBJ_DIR_BNS	=	./obj_bns/
INC_DIR		=	./bonus/
MLX42_DIR   =	./MLX42


# controll codes
RESET		=	\033[0m
GREEN		=	\033[32m
YELLOW		=	\033[33m
BLUE		=	\033[34m
RED			=	\033[31m
UP			=	\033[A
CUT			=	\033[K

#source files
SRC_FILES	=	parsing/parsing.c \
				parsing/skipping_t_n_s.c \
				parsing/counting_mapsize.c \
				parsing/loading_utils.c \
				parsing/loading_utils2.c \
				game_logic/game_hooks.c \
				game_logic/launch.c \
				game_logic/player_mouvements.c \
				game_logic/walls_checker.c \
				ray_casting/casting_init.c \
				ray_casting/casting_utils.c \
				ray_casting/horizontal_checker.c \
				ray_casting/vertical_checker.c \
				ray_casting/ray_casting.c \
				rendering/drawing_rays.c \
				rendering/render_map.c \
				texture_rendring/loading_png.c \
				texture_rendring/texture.c \
				cub3D.c

FILES_BNS	=	parsing/parsing.c \
				parsing/skipping_t_n_s.c \
				parsing/counting_mapsize.c \
				parsing/loading_utils.c \
				parsing/loading_utils2.c \
				game_logic/game_hooks.c \
				game_logic/launch.c \
				game_logic/player_mouvements.c \
				game_logic/walls_checker.c \
				ray_casting/casting_init.c \
				ray_casting/casting_utils.c \
				ray_casting/horizontal_checker.c \
				ray_casting/vertical_checker.c \
				ray_casting/ray_casting.c \
				rendering/drawing_rays.c \
				rendering/render_map.c \
				texture_rendring/loading_png.c \
				texture_rendring/texture.c \
				cub3D_bonus.c

INC_FILES		=	cub3D.h
INC_FILES_BNS	=	./bonus/cub3D.h

OBJ_FILES		=	$(SRC_FILES:.c=.o)
OBJ_FILES_BONUS	=	$(FILES_BNS:.c=.o)

#paths
SRC			=	$(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ			=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))
SRC_BNS		=	$(addprefix $(BNS_DIR), $(FILES_BNS))
OBJ_BNS		=	$(addprefix $(OBJ_DIR_BNS), $(OBJ_FILES_BONUS))

                                                                                
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
$(NAME): mlx42 $(OBJ) $(INC_FILES)
	@echo "$(YELLOW)Compiling [$(NAME)]...$(RESET)"
	@(cd libft; make)
	@(cd $(MLX42_DIR); cmake -B build; cmake --build build -j4);
	@$(CC) $(CFLAGS) $(CMLX42) $(OBJ) ./libft/libft.a -o $(NAME)
	@echo "$(GREEN)Finished [$(NAME)]$(RESET)"

bonus : $(BONUS)

#compile objects
$(OBJ_DIR)%.o:$(SRC_DIR)%.c $(INC_FILES)
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling [$@]...$(RESET)"
	@$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<
	@printf "$(UP)$(CUT)"
	@echo "$(GREEN)Finished [$@]$(RESET)"
	@printf "$(UP)$(CUT)"

#BONUS
$(BONUS): mlx42 $(OBJ_BNS) $(INC_FILES_BNS)
	@echo "$(YELLOW)Compiling [$(BONUS)]...$(RESET)"
	@(cd libft; make)
	@(cd $(MLX42_DIR); cmake -B build; cmake --build build -j4);
	@$(CC) $(CFLAGS) $(CMLX42) $(OBJ_BNS) ./libft/libft.a -o $(BONUS)
	@echo "$(GREEN)Finished [$(BONUS)]$(RESET)"

$(OBJ_DIR_BNS)%.o:$(BNS_DIR)%.c $(INC_FILES_BNS)
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling [$@]...$(RESET)"
	@$(CC) $(CFLAGS) -I $(INC_FILES_BNS) -o $@ -c $<
	@printf "$(UP)$(CUT)"
	@echo "$(GREEN)Finished [$@]$(RESET)"
	@printf "$(UP)$(CUT)"

mlx42:
	@[ -d MLX42 ] || git clone https://github.com/codam-coding-college/MLX42.git MLX42 


#clean rule
clean:
	@rm -rf $(OBJ_DIR_BNS)
	@if [ -d "$(OBJ_DIR)" ]; then \
	rm -rf $(OBJ_DIR); \
	echo "$(BLUE)Deleting all objects from /Cub3D...$(RESET)"; else \
	echo "No objects to remove from /Cub3D."; \
	fi;

#fclean rule
fclean: clean
	@rm -rf $(MLX42_DIR)
	@rm -rf $(BONUS)
	@if [ -f "$(NAME)" ]; then \
	rm -f $(NAME); \
	cd ./libft; make fclean; \
	echo "$(BLUE)Deleting $(NAME) from /Cub3D...$(RESET)"; else \
	echo "No Executable to remove from /Cub3D."; \
	fi;

#re rule
re: fclean all bonus

#phony
.PHONY: all clean fclean re                                                                                  