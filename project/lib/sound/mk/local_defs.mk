NAME=		./../../../music/lib_arcade_sound.so

BASE_NAME=	lib_arcade_sound.so

LOCAL_CXXFLAGS= -fPIC -I./include -I./../../../include

LOCAL_LDFLAGS= -shared -lsfml-audio
