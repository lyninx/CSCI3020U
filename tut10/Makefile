# the compiler: gcc for C program, define as g++ for C++
CC = mpicc
# set as gcc if you don't have clang

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings

CFLAGS  = -Wall -Wextra -std=c99

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
LIBS = 

LIST = question1 question2 question3 question4

all: $(LIST)

question1:
	$(CC) $(CFLAGS) $(LIBS) demo_1.c -o demo_1.exe
	$(CC) $(CFLAGS) $(LIBS) demo_2.c -o demo_2.exe

question2: question2.c
	$(CC) $(CFLAGS) $(LIBS) question2.c -o question2.exe -lm

question3: question3.c
	$(CC) $(CFLAGS) $(LIBS) question3.c -o question3.exe -lm

question4: question4.c
	$(CC) $(CFLAGS) $(LIBS) question4.c -o question4.exe -lm

clean:
	$(RM) *.exe