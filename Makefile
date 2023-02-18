# Makefile

CC = gcc
CPPFLAGS = -MMD
CFLAGS = #-Wall -Wextra #-fsanitize=address
LDFLAGS = -fsanitize=address
LDLIBS = -lm
OUTPUT = bin

TARGET = $(OUTPUT)/main
TITLE = Engine

ListDir = Libs/List src/ParticuleEngine
#print all folder in ListDir
#$(info $(ListDir))

SRC = $(wildcard *.c) $(wildcard src/*.c) $(foreach folder,$(ListDir),$(wildcard $(folder)/*.c))
OBJ = ${SRC:.c=.o}
DEP= ${SRC:.c=.d}
PRG= ${SRC:.c=}

ifeq (win_mode,$(MAKECMDGOALS))###########################################################################################################

#WINDOWS COMPILATION
CC = gcc
#sdl_mode: CFLAGS += -DWIN_MODE `pkg-config --cflags sdl2 SDL2_image SDL2_ttf`
#sdl_mode: LDLIBS += `pkg-config --libs sdl2 SDL2_image SDL2_ttf`
CFLAGS += -I Libs/SDL2_WIN_Include/include -I Libs/List -DWIN_MODE -DWIN32
LDLIBS += -L Libs/SDL2_WIN_Include/lib -L Libs/List -lmingw32 -lSDL2 -lgdi32 -luser32 -lole32 -loleaut32 -lmingw32 -limm32 -lwinmm -lversion -lSetupAPI -lSDL2 -lSDL2_image -lSDL2_ttf -lfreetype

#copy all file in Libs/BIN_SDL to bin folder
win_mode: ${OBJ}
	$(CC) $(CFLAGS) -o $(TARGET).exe $(OBJ) $(LDLIBS)
	cp Libs/BIN_SDL/* $(OUTPUT)


$(foreach f, $(TARGET), $(eval $(f):))

-include ${DEP}

.PHONY: clean

# END
endif

ifeq (psp_mode,$(MAKECMDGOALS))###########################################################################################################

#PSP COMPILATION
OBJS = $(OBJ) Libs/PSP/common/callbacks.o Libs/PSP/common/common-sce.o

INCDIR = $(ListDir)
LIBS= $(LDLIBS) -lpspgum -lpspgu -lm -lpspaudio -lpspmp3 -lpspaudiocodec -lpspaudiolib -lpspsdk -lpsprtc
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR =
LDFLAGS =

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = $(TITLE)

#add -DPSP_MODE
CFLAGS += -DPSP_MODE

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
#move EBOOT.PBP to bin folder
psp_mode: all
	mv $(EXTRA_TARGETS) $(OUTPUT)/$(EXTRA_TARGETS)
	mv PARAM.SFO $(OUTPUT)/PARAM.SFO
endif

ifeq (nds_mode,$(MAKECMDGOALS))###########################################################################################################



endif



ifeq (clean,$(MAKECMDGOALS))

clean:
	$(RM) $(OBJ)
	$(RM) $(EXE)
	rm -f *.o
	rm -f ${DEP}
	rm -f ${PRG}
	$(RM) -f $(EXE)
	$(RM) -f $(OUTPUT)/*
	$(RM) -f Libs/PSP/common/*.o
	$(RM) -f Libs/PSP/common/*.d

endif