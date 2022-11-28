CONSOLE_ENABLE=yes

dokurocker_dvorakjp_DEFS :=  -DDOKU_MOCKED

dokurocker_dvorakjp_SRC := \
	keyboards/crkbd/keymaps/dokurocker/dvorakjp/dvorakjp.c \
	keyboards/crkbd/keymaps/dokurocker/dvorakjp/tests/dvorakjp_tests.cpp \
	keyboards/crkbd/keymaps/dokurocker/dvorakjp/tests/mock.c \
	$(QUANTUM_PATH)/logging/print.c

dokurocker_dvorakjp_INC := \
	keyboards/crkbd/keymaps/dokurocker/


