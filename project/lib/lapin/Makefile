MK_THIS=	./mk/
MK_COMMON_DIR=	./../../../mk/

include $(MK_COMMON_DIR)defs.mk $(MK_THIS)local_defs.mk

SRC=	$(addprefix ./src/,	\
	libLapin.cpp		\
	KeyMap.cpp		\
	)

SRC+=	$(addprefix ./../../common/,	\
	Color.cpp			\
	)

include $(MK_COMMON_DIR)rules.mk
