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

LIST = basic_locking basic_thread locking fork_example semaphore notify n_notify bounded_notify semaphore_buffer

all: $(LIST)

q1: basic_locking.c
	$(CC) $(CFLAGS) quesstion1.c -o q1 $(LIBS)

q2: basic_thread.c
	$(CC) $(CFLAGS) question2.c -o q2 $(LIBS)

clean:
	$(RM) $(LIST)