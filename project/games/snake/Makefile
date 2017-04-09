MK_THIS=	./mk/
MK_COMMON_DIR=	./../../../mk/

include $(MK_COMMON_DIR)defs.mk $(MK_THIS)local_defs.mk

SRC=	$(addprefix ./src/,	\
	libSnake.cpp		\
	play.cpp		\
	)
SRC+=	$(addprefix ../common/src/,	\
	GameGUI.cpp			\
	gameCommon.cpp			\
	)
SRC+=	$(addprefix ./../../common/,	\
	$(COMMON_SRC)			\
	)

include $(MK_COMMON_DIR)rules.mk
