CXX=		clang++

DEBUG=		yes

CXXFLAGS=	-W -Wall -Wextra -Wpointer-arith -Wshadow -std=c++14

LDFLAGS=	""

RM=		rm -f

SRC=		""

OBJ=		""

ifeq ($(DEBUG), yes)
  CXXFLAGS+= -g
endif
