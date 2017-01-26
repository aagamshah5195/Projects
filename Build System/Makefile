
#This is a Makefile for the project.

include sources.mk

all: main.o project_1.o memory.o data.o compile-all build clean

.PHONY: %.i asm-file %.o compile-all build clean

#Declare the variables

CFLAGS= -Wall -std=c99 -g -O0

CPFLAGS = -I$(DIR_HEADER)

CFPFLAGS = -I$(DIR_HEADER1)

#Link flag defined
LDFLAGS = -Wl,-Map=project.map

#ARM compiler command
BBB = arm-linux-gnueabihf-gcc 

#FRDM compiler command
FRDM= arm-none-eabi-gcc --specs=nosys.specs -DFRDM

#GCC compiler command
HOST = gcc

#VARIABLE defined to combine flags
CC = $(HOST) $(CFLAGS)

#VARIABLE defined to combine flags
CCBB = $(BBB) $(CFLAGS)

#VARIABLE defined to combine flags
CCFR = $(FRDM) $(CFLAGS)

#Create Preprocess file	
%.i: %.c
	mkdir -p source/preprocess
	$(CC) $(CFLAGS) -E $< 
	cpp $< > $@ 
	mv *.i source/preprocess

file.i: $(CFILES)
	mkdir -p source/preprocess
	$(CC) $(CFLAGS) -E $< 
	cpp $< > $@ 
	mv *.i source/preprocess

#Create Assembly file
file.s: $(CFILES)
	mkdir -p source/asm
	$(CC) $(CFLAGS) -S $^
	mv *.s source/asm
%.s: %.c
	mkdir -p source/asm
	$(CC) $(CFLAGS) -S $^
	mv *.s source/asm

#Create Output file
%.o: %.c
	mkdir -p source/output
	$(CC) -c $(CFLAGS) $^
	objdump -f $@
	mv *.o source/output 

#Compile all files
compile-all:$(CFILES) 
	mkdir -p source/object
	$(CC) -c $(CPFLAGS) $^
	mv *.o source/object

compile-all-BBB:$(CFILES)
	mkdir -p source/object_cross
	$(CCBB) -c $^ $(CPFLAGS)
	mv *.o source/object_cross

compile-all-FRDM:$(CFFILES)
	mkdir -p source/FRDM/object_cross
	$(CCFR) -c $^ $(CFPFLAGS)
	mv *.o source/FRDM/object_cross
	
#Compile and Link all files
build: $(OBJ)
	$(CC) -o project $^ $(CPFLAGS) $(LDFLAGS)
	$(CC) -MM source/main.c source/data.c source/project_1.c source/memory.c source/data.h source/memory.h source/project_1.h > deps
	size project

build-BBB:$(OBJCROSS)
	$(CCBB) -o project $^ $(CPFLAGS)
	size project

build-FRDM:$(OBJCROSS1)
	$(CCFR) -o project $^ $(CFPFLAGS)
	size project

#Upload Project to BBB
upload: 
	scp project root@192.168.7.2:/home/debian/bin

#Clean all the unwanted files
clean:
	rm -rf source/preprocess/*.i	
	rm -rf source/object/*.o
	rm -rf source/object_cross/*.o 
	rm -rf source/*.c~ 
	rm -rf source/asm/*.s 
	rm -rf *.out *.map project
	rm -rf source/object/*.gch
	rm -rf source/object/*.h~
	rm -rf -r source/object src/asm src/object_cross

#Creates an archieve of library files
build_lib:
	ar rcs libproject1.a *.c
	
