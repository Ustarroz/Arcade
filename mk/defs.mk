CXX=		g++

DEBUG=		yes

CXXFLAGS=	-W -Wall -Wextra -Wpointer-arith -Wshadow -std=c++14

LDFLAGS=

RM=		rm -f

SRC=		""

COMMON_SRC=	Color.cpp	\
		Component.cpp	\
		GUI.cpp		\
		Layer.cpp	\
		Map.cpp		\
		Tile.cpp

OBJ=		""

BASE_DIR=	$(CURDIR)

ifeq ($(DEBUG), yes)
  CXXFLAGS+= -g
endif
