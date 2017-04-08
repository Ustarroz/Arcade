PROJECT_DIR=	./project/core/ 	\
		./project/games/snake/	\
		./project/lib/caca/ 	\
		./project/lib/sdl/
		#./project/lib/sound/	\
		#./project/games/menu/
		#./project/lib/lapin/ 	\
		#./project/games/centipede/	\

all:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) && ) true

clean:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) clean && ) true

fclean:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) fclean && ) true

re:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) re && ) true

