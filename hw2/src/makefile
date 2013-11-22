#make file contents and construction

#basic layout of makefile

#	target:	prerequsites
#[tab]	command

#Define variables

CC	= g++ -v	#compiler
LD	= ld		#linker
CFLAGS	= -g -c -Wall -std=c++0x -I../include	#compiler flags
#LDFLAGS	= -L/usr/include -L/usr/include/local	#linker flags 
RM	= -rm -f	#remove files


all: hw2.exe

# here output file can be mentioned as 'hw2.exe' or '$@'
hw2.exe: hw2.o
	$(CC) -o $@ hw2.o 

# here source/input file cane be named 'hw2.cpp' or '$<'
hw2.o: hw2.cpp Graph.h
	$(CC) $(CFLAGS) $< 
 
clean:
	$(RM) *.o *.exe

