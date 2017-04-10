NAME=		./../../../lib_arcade_lapin.so

BASE_NAME=	lib_arcade_lapin.so

LOCAL_CXXFLAGS= -fPIC -I./include -I./../../../include

LOCAL_LDFLAGS= -shared -L~/ -llapin -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lstdc++ -lm -ldl -lpthread
