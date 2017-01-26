#Includes All the Source Files
CFILES = memory.c data.c project_1.c main.c

CFFILES = memoryFRDM.c dataFRDM.c projectFRDM_1.c mainFRDM.c

#Includes All the Header Files
HFILES= memory.h data.h project_1.h

HFFILES= memoryFRDM.h dataFRDM.h project_1FRDM.h

#Includes All the Object File
OBJS = data.o memory.o main.o project_1.o

#Includes All the object files for BBB
OBJSCROSS = data.o memory.o main.o project_1.o

#Includes All the object files for FRDM
OBJSCROSS1 = dataFRDM.o memoryFRDM.o mainFRDM.o projectFRDM_1.o

#PATH DIRECTORIES
DIR_HEADER = source/object

DIR_HEADER1 = source/FRDM/object

DIR_OBJ = source/object

DIR_OBJCROSS=source/object_cross

DIR_OBJCROSS1=source/FRDM/object_cross

VPATH= source:../object

HEADER = $(patsubst %,$(DIR_HEADER)/%,$(HFILES))

HEADER1 = $(patsubst %,$(DIR_HEADER1)/%,$(HFFILES))

OBJ = $(patsubst %,$(DIR_OBJ)/%,$(OBJS))

OBJCROSS = $(patsubst %,$(DIR_OBJCROSS)/%,$(OBJSCROSS))

OBJCROSS1 = $(patsubst %,$(DIR_OBJCROSS1)/%,$(OBJSCROSS1))









