NAME=		./../../../games/lib_arcade_snake.so

BASE_NAME=	lib_arcade_snake.so

LOCAL_CXXFLAGS= -fPIC -I./include -I./../../../include

LOCAL_LDFLAGS= -shared -lSDL2
