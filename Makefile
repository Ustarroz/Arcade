PROJECT_DIR=	./project/core/ 		\
		./project/lib/caca/ 		\
		./project/lib/sdl/		\
		./project/games/menu/		\
		./project/games/snake/		\
		./project/games/centipede/
		#./project/lib/sound/		\
		#./project/lib/lapin/


all:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) && ) true

clean:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) clean && ) true

fclean:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) fclean && ) true

re:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) re && ) true

