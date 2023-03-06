# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = #-Wall -Wextra #-fsanitize=address
LDFLAGS = -fsanitize=address
LDLIBS = -lm
OUTPUT = bin
BUILD =	build

TITLE = Engine

TARGET = $(OUTPUT)/$(TITLE)

ListDir = Libs/List src/ParticuleEngine src/Rpg src/InterfaceSystem src/ScriptEditor
#print all folder in ListDir
#$(info $(ListDir))


SRC = $(wildcard *.c) $(wildcard src/*.c) $(foreach folder,$(ListDir),$(wildcard $(folder)/*.c))
OBJ = ${SRC:.c=.o}
DEP= ${SRC:.c=.d}
PRG= ${SRC:.c=}

ifeq (win_mode,$(MAKECMDGOALS))###########################################################################################################

include $(CURDIR)/MakefileWin


# END
endif

ifeq (linux_mode,$(MAKECMDGOALS))###########################################################################################################

include $(CURDIR)/MakefileLinux


# END
endif

ifeq (psp_mode,$(MAKECMDGOALS))###########################################################################################################

include $(CURDIR)/MakefilePSP

endif

ifeq (nds_mode,$(MAKECMDGOALS))###########################################################################################################

include $(CURDIR)/MakefileDS

endif

ifeq (n3ds_mode,$(MAKECMDGOALS))###########################################################################################################

TARGET = $(TITLE)
OUTPUTDIR = $(CURDIR)/bin

include $(CURDIR)/Makefile3DS

endif

ifeq (clean,$(MAKECMDGOALS))

.PHONY: clean

clean:
	rm -rf $(BUILD)/*
	$(RM) $(OBJ)
	$(RM) $(EXE)
	rm -f *.o
	rm -f ${DEP}
	rm -f ${PRG}
	$(RM) -f $(EXE)
	$(RM) -rf $(OUTPUT)/*
	$(RM) -f Libs/PSP/common/*.o
	$(RM) -f Libs/PSP/common/*.d

endif