# the compiler: gcc for C program, define as g++ for C++
CC = clang
# set as gcc if you don't have clang

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -std=c99

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

LIST = q1 q2 q3 q4 q5

all: $(LIST)

q1: question1.c
	$(CC) $(CFLAGS) question1.c -o q1.exe $(LIBS)

q2: question2.c
	$(CC) $(CFLAGS) question2.c -o q2.exe $(LIBS)

q3: question3.c
	$(CC) $(CFLAGS) question3.c -o q3.exe $(LIBS)

q4: question4.c
	$(CC) $(CFLAGS) question4.c -o q4.exe $(LIBS)

q5: question5.c
	$(CC) $(CFLAGS) question5.c -o q5.exe $(LIBS)

clean:
	$(RM) *.exe