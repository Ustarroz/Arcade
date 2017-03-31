PROJECT_DIR=	./project/core/ 	\
		./project/lib/sdl/ 	\
		./project/lib/lapin/ 	\
		./project/lib/caca/ 	\

all:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -C $(c) && ) true

clean:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -C $(c) clean && ) true

fclean:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -C $(c) fclean && ) true

re:
		@$(foreach c, $(PROJECT_DIR), $(MAKE) -C $(c) re && ) true

