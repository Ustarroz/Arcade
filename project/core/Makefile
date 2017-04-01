MK_THIS=	./mk/
MK_COMMON_DIR=	./../../mk/

include $(MK_COMMON_DIR)defs.mk $(MK_THIS)local_defs.mk

SRC=	$(addprefix ./src/,	\
	main.cpp		\
	Core.cpp 		\
	)

COMMON_SRC= $(addprefix ./../common/,	\
	    Component.cpp 		\
	    GUI.cpp 			\
	    Color.cpp 			\
	    )

SRC+=	$(COMMON_SRC)

include $(MK_COMMON_DIR)rules.mk
