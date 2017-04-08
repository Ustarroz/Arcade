MK_THIS=	./mk/
MK_COMMON_DIR=	./../../../mk/

include $(MK_COMMON_DIR)defs.mk $(MK_THIS)local_defs.mk

SRC=	$(addprefix ./src/,	\
	libCentipede.cpp		\
	CentipedeGUI.cpp		\
	)
SRC+=	$(addprefix ./../../common/,	\
	$(COMMON_SRC)			\
	)

include $(MK_COMMON_DIR)rules.mk
