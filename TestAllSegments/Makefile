# Makefile for STM8 uC

DEBUG= 0

CC_PATH= 
CC= $(CC_PATH)sdcc
LIBS= -lstm8 -mstm8
CC_FLAGS= -I$(LIBINCDIR_PATH) -I$(DRVINCDIR_PATH) -I$(APPINCDIR_PATH) -I$(UTILINCDIR_PATH)
PREPROC_MACROS= -DSTM8S103 -D__CSMC__
LD_FLAGS:= $(LIBS)

ifeq ($(OUTPUT_FILE_FRMT), MOTOROLA)
	OUT_FILE_FORMAT= --out-fmt-s19
else
	OUT_FILE_FORMAT= --out-fmt-ihx
endif


# Project Root Directory
ROOTDIR_PATH= /media/d7/Data/ProjectData/Arm/Stm8/

# Stm8 Library paths
LIBDIR_PATH= $(ROOTDIR_PATH)/STM8Library/
LIBSRCDIR_PATH= $(LIBDIR_PATH)/src
LIBINCDIR_PATH= $(LIBDIR_PATH)/inc

# Peripheral Driver paths
DRVLIBDIR_PATH= $(ROOTDIR_PATH)/DriverLibrary/
DRVSRCDIR_PATH= $(DRVLIBDIR_PATH)/Src
DRVINCDIR_PATH= $(DRVLIBDIR_PATH)/Inc

# Utility code 
UTILDIR_PATH= $(ROOTDIR_PATH)/Utils/
UTILSRCDIR_PATH=$(UTILDIR_PATH)/Src
UTILINCDIR_PATH=$(UTILDIR_PATH)/Inc

# Application related variables
APP_NAME= TestAllSegments
APPDIR_PATH= $(ROOTDIR_PATH)/$(APP_NAME)
BUILDDIR_PATH= $(APPDIR_PATH)/Build
APPSRCDIR_PATH= $(APPDIR_PATH)/Src
APPINCDIR_PATH= $(APPDIR_PATH)/Inc
OBJDIR_PATH= $(APPDIR_PATH)/Obj
EXE= $(APP_NAME).ihx

ifeq ($(DEBUG), 1)
	CC_FLAGS := $(CC_FLAGS) 
else
endif


VPATH:= $(LIBSRCDIR_PATH):$(DRVSRCDIR_PATH):$(UTILSRCDIR_PATH):$(APPSRCDIR_PATH)

SRCS= app.c stm8s_gpio.c stm8s_conf.c tm1637.c timedelay.c 
OBJS= $(patsubst %.c, $(OBJDIR_PATH)/%.rel, $(SRCS))

.PHONY: all clean build flash

all : clean makdir build 
makdir:
	mkdir -p $(OBJDIR_PATH)
	mkdir -p $(BUILDDIR_PATH)

# Automatic Variables
# $@ - Contains target file name
# $< - Contains 1st dependency file name
$(OBJDIR_PATH)/%.rel: %.c
		$(CC) $(PREPROC_MACROS) $(CC_FLAGS) $(LIBS) -c $< -o$(OBJDIR_PATH)/

build:	$(OBJS)
	$(CC) $(OBJS) $(LIBS) $(OUT_FILE_FORMAT) -o $(BUILDDIR_PATH)/$(EXE) 
		
flash: $(BUILDDIR_PATH)/$(EXE)
	stm8flash -cstlinkv2 -pstm8s103f3 -w$(BUILDDIR_PATH)/$(EXE) 

clean :
	rm -f $(OBJDIR_PATH)/* $(BUILDDIR_PATH)/* 


