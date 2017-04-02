PROJECT_DIR=	./project/core/ 	\
		./project/lib/sdl/ 	\
		./project/games/snake/
		#./project/lib/lapin/ 	\
		#./project/lib/caca/ 	\

all:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) && ) true

clean:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) clean && ) true

fclean:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) fclean && ) true

re:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -s -C $(c) re && ) true

