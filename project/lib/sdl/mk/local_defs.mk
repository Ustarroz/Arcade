NAME=		./../../../lib/lib_arcade_sdl.so

BASE_NAME=	lib_arcade_sdl.so

LOCAL_CXXFLAGS= -fPIC -I./include -I./../../../include

LOCAL_LDFLAGS= -shared -lSDL2 -lSDL2_ttf
