PROJECT_DIR=	./project/lib/caca/ 		\
		./project/lib/sdl/		\
		./project/lib/sound/		\
		./project/games/snake/		\
		./project/games/centipede/	\
		./project/lib/lapin/		\
		./project/core/


all:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) && ) true

clean:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) clean && ) true

fclean:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) fclean && ) true

re:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) re && ) true

