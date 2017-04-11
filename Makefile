PROJECT_DIR=	./project/core/ 		\
		./project/lib/caca/ 		\
		./project/lib/sdl/		\
		./project/lib/lapin/		\
		./project/games/snake/
		#./project/lib/sound/		\
		#./project/games/menu/		\
		#/project/games/centipede/

all:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) && ) true

clean:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) clean && ) true

fclean:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) fclean && ) true

re:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) re && ) true

