NAME=		./../../../games/lib_arcade_centipede.so

BASE_NAME=	lib_arcade_centipede.so

LOCAL_CXXFLAGS= -fPIC -I./include -I./../../../include

LOCAL_LDFLAGS= -shared -lSDL2
