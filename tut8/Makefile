# the compiler: gcc for C program, define as g++ for C++
CC = clang
# set as gcc if you don't have clang

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings

CFLAGS  = -g -Wall -Wextra -std=gnu99

# define any directories containing header files other than /usr/include
# -I/home/newhall/include  -I../include
INCLUDES = 

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS =

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
LIBS = -lpthread

LIST = question1 question2

all: $(LIST)

question1: question1.c
	$(CC) $(CFLAGS) $(LIBS) question1.c -o question1.exe

question2: question2.c
	$(CC) $(CFLAGS) $(LIBS) queue.c question2.c -o question2.exe

clean:
	$(RM) *.exe