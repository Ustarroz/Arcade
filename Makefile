DEBUG=		yes

NAME=		arcade

CXX=		clang++

SRC_CORE=	$(addprefix ./src/core/,	\
		main.cpp			\
		Core.cpp 			\
		)

OBJ_CORE=	$(SRC_CORE:.cpp=.o)

SRC_SDL=	$(addprefix ./src/lib/sdl/,	\
		libSDL.cpp			\
		)

OBJ_SDL=	$(SRC_SDL:.cpp=.o)

CXXFLAGS=		-W -Wall -Wextra -Wpointer-arith -Wshadow -fstack-protector

CXXFLAGS+=	-I./include/

LDFLAGS=	""

ifeq ($(DEBUG), yes)
  CXXFLAGS+= -g
endif

$(NAME):	$(OBJ_CORE)
		@$(CXX) -o $(NAME) $(OBJ_CORE) $(LDFLAGS)
		@echo "options: $(CXXFLAGS)"

libs:
		$(CXX)-shared -o lib_arcade_sdl.so -fPIC $(SRC_SDL) $(CXXFLAGS)
		

all: 		$(NAME) libs

%.o:		%.cpp
		@echo "process $<"
		@$(CXX) -c -o $@ $< $(CXXFLAGS)

clean:
		rm -rf $(OBJ_CORE)

fclean: 	clean
		rm -rf $(NAME)

re: 		fclean all

.PHONY: re fclean clean all
