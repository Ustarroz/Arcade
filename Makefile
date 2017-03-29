DEBUG=		yes

NAME=		arcade

CXX=		clang++

SRC_CORE=	$(addprefix ./src/core/,	\
		main.cpp			\
		)

OBJ_CORE=	$(SRC_CORE:.c=.o)

CFLAGS=		-W -Wall -Wextra -Wpointer-arith -Wshadow -fstack-protector

CFLAGS+=	-I./include

LDFLAGS=	""

ifeq ($(DEBUG), yes)
  CFLAGS+= -g

libs:
	echo "compiling libs"

games:
	echo "compiling games"

core:	$(OBJ_CORE)
	echo "compiling core"
	$(CXX) -o $(NAME) $(OBJ_CORE) $(LDFLAGS)

all: 	libs games core

%.o:	%.c
	echo $<
	$(CXX) -c -o $@ $< $(CFLAGS)

clean:
	rm -rf $(OBJS)

flcean: clean
	rm -rf $(NAME)

.PHONY: re fclean clean all core games libs
