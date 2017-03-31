CXX=		clang++

DEBUG=		yes

CXXFLAGS=	-W -Wall -Wextra -Wpointer-arith -Wshadow -std=c++14

LDFLAGS=	""

RM=		rm -f

SRC=		""

OBJ=		""

BASE_DIR=	$(CURDIR)

ifeq ($(DEBUG), yes)
  CXXFLAGS+= -g
endif
